#include <kamek.h>
#include <fBase/dBase/dBaseActor/dActor/dActor.h>
#include <m/m3d/camera.h>
#include <nw4r/g3d/camera.h>
#include <nw4r/math/triangular.h>
#include <rvl/gx/GXCull.h>
#include <rvl/gx/GXEnum.h>
#include <rvl/gx/GXGeometry.h>
#include <rvl/gx/GXLighting.h>
#include <rvl/gx/GXPixel.h>
#include <rvl/gx/GXStruct.h>
#include <rvl/gx/GXTev.h>
#include <rvl/gx/GXTransform.h>
#include <rvl/gx/GXVert.h>
#include <dBc.h>
#include <dBg_ctr.h>
#include <dCc.h>
#include <dRide_ctr.h>
#include <dRideCircle.h>
#include "debug/collisionRender.h"
#include "debug/config.h"

// Patches to allow tracking instances of dBc_c
static dBc_c* firstBc = NULL;
static dBc_c* lastBc = NULL;

extern "C" {
void addBcToList(dBc_c* self);
void removeBcFromList(dBc_c* self);
}

// Drawing helper functions
void DrawPoint(float x, float y, float z, u8 r, u8 g, u8 b, u8 a) {
    GXBegin(GXPrimitive::POINTS, 0, 1);

    GXPosition3f32(x, y, z);
    GXColor4u8(r,g,b,a);

    GXEnd();
}

void DrawLine(float x1, float y1, float x2, float y2, float z, u8 r, u8 g, u8 b, u8 a) {
    GXBegin(GXPrimitive::LINES, 0, 2);

    GXPosition3f32(x1, y1, z);
    GXColor4u8(r,g,b,a);
    GXPosition3f32(x2, y2, z);
    GXColor4u8(r,g,b,a);

    GXEnd();
}

void DrawQuad(float tlX, float tlY, float trX, float trY, float blX, float blY, float brX, float brY, float z, u8 r, u8 g, u8 b, u8 a, bool addDiagonal) {

    // Setup drawing
    GXBegin(GXPrimitive::LINES, 0, 8 + addDiagonal * 2);

    // Draw top
    GXPosition3f32(tlX, tlY, z);
    GXColor4u8(r,g,b,a);
    GXPosition3f32(trX, trY, z);
    GXColor4u8(r,g,b,a);

    // Draw left
    GXPosition3f32(tlX, tlY, z);
    GXColor4u8(r,g,b,a);
    GXPosition3f32(blX, blY, z);
    GXColor4u8(r,g,b,a);

    // Draw right
    GXPosition3f32(trX, trY, z);
    GXColor4u8(r,g,b,a);
    GXPosition3f32(brX, brY, z);
    GXColor4u8(r,g,b,a);

    // Draw bottom
    GXPosition3f32(blX, blY, z);
    GXColor4u8(r,g,b,a);
    GXPosition3f32(brX, brY, z);
    GXColor4u8(r,g,b,a);

    // Draw diagonal if enabled
    if (addDiagonal) {
        GXPosition3f32(trX, trY, z);
        GXColor4u8(r,g,b,a);
        GXPosition3f32(blX, blY, z);
        GXColor4u8(r,g,b,a);
    }

    GXEnd();
}

// Credits to Ismy for helping me with this one
void DrawCircle(float centreX, float centreY, float radiusX, float radiusY, float z, u8 r, u8 g, u8 b, u8 a) {

    // Define a few variables
    const int numVert = 64;
    const float step = 256.0f/numVert;
    float sin, cos, xDist, yDist;

    // Initialize the prev variables
    float prevXDist = radiusX;
    float prevYDist = 0.0f;

    // Begin drawing
    GXBegin(GXPrimitive::LINES, 0, numVert * 2);

    // Draw each line
    for (int i = 1; i <= numVert / 4; i++) {

        // Calculate sin and cos for the current angle
        nw4r::math::SinCosFIdx(&sin, &cos, step * i);

        // Calculate the distances from the center
        xDist = radiusX * cos;
        yDist = radiusY * sin;

        // Draw on the first quadrant
        GXPosition3f32(centreX + prevXDist, centreY + prevYDist, z);
        GXColor4u8(r,g,b,a);
        GXPosition3f32(centreX + xDist, centreY + yDist, z);
        GXColor4u8(r,g,b,a);

        // Draw on the second quadrant
        GXPosition3f32(centreX - prevYDist, centreY + prevXDist, z);
        GXColor4u8(r,g,b,a);
        GXPosition3f32(centreX - yDist, centreY + xDist, z);
        GXColor4u8(r,g,b,a);

        // Draw on the third quadrant
        GXPosition3f32(centreX - prevXDist, centreY - prevYDist, z);
        GXColor4u8(r,g,b,a);
        GXPosition3f32(centreX - xDist, centreY - yDist, z);
        GXColor4u8(r,g,b,a);

        // Draw on the fourth quadrant
        GXPosition3f32(centreX + prevYDist, centreY - prevXDist, z);
        GXColor4u8(r,g,b,a);
        GXPosition3f32(centreX + yDist, centreY - xDist, z);
        GXColor4u8(r,g,b,a);

        // Override the "previous" values
        prevXDist = xDist;
        prevYDist = yDist;
    }

    // End drawing
    GXEnd();
}

void DrawPartialCircle(float centreX, float centreY, float radius, float z, u16 minAngle, u16 maxAngle, u8 r, u8 g, u8 b, u8 a) {

    // Initialize variables
    const int maxVerts = 64;
    const float step = 256.0f/maxVerts;
    float sin, cos, xDist, yDist;

    // Calculate the number of required vertices and the starting angle
    u16 totalAngle = (maxAngle - minAngle) & 0xFFFF;
    int numVert = (totalAngle * maxVerts / 0x10000);
    float startAngle = minAngle / 256.0f;

    // Set up the prev variables
    nw4r::math::SinCosFIdx(&sin, &cos, startAngle);
    float prevXDist = radius * cos;
    float prevYDist = radius * sin;

    // Begin drawing
    GXBegin(GXPrimitive::LINES, 0, numVert * 2);

    // Draw each line
    for (int i = 1; i <= numVert; i++) {

        // Calculate sin and cos for the current angle
        nw4r::math::SinCosFIdx(&sin, &cos, startAngle + step * i);

        // Calculate the distances from the center
        xDist = radius * cos;
        yDist = radius * sin;

        // Draw the line
        GXPosition3f32(centreX + prevXDist, centreY + prevYDist, z);
        GXColor4u8(r,g,b,a);
        GXPosition3f32(centreX + xDist, centreY + yDist, z);
        GXColor4u8(r,g,b,a);

        // Override the "previous" values
        prevXDist = xDist;
        prevYDist = yDist;
    }
}

static dCollisionRenderProc_c instance;

dCollisionRenderProc_c::dCollisionRenderProc_c() {
    this->create(NULL, NULL);
}

// Dummy function
void dCollisionRenderProc_c::drawOpa() {
}

// Actual drawing
void dCollisionRenderProc_c::drawXlu() {

    // Setup copied from 0x801717C0
    // Set current vertex descriptor to enable position and color0, both provided directly
    GXClearVtxDesc();
    GXSetVtxDesc(GXAttr::POS, GXAttrType::DIRECT);
    GXSetVtxDesc(GXAttr::CLR0, GXAttrType::DIRECT);

    // Position has 3 elements (x,y,z), each of type f32
    GXSetVtxAttrFmt(0, GXAttr::POS, GXCompCnt::POS_XYZ, GXCompType::F32, 0);

    // Color 0 has 4 components (r, g, b, a), each of type u8
    GXSetVtxAttrFmt(0, GXAttr::CLR0, GXCompCnt::CLR_RGBA, GXCompType::RGBA8, 0);

    // Disable culling
    GXSetCullMode(GXCullMode::NONE);

    // Enable color channel 0 and set vertex color as source
    GXSetNumChans(1);
    GXSetChanCtrl(GXChannelID::COLOR0A0, false, GXColorSrc::VTX, GXColorSrc::VTX, GXLightID::NONE, GXDiffuseFn::OFF, GXAttnFn::NONE);
    GXSetNumTexGens(0);

    // Enable one TEV stage
    GXSetNumTevStages(1);
    GXSetTevOp(0, GXTevMode::PASSCLR);
    GXSetTevOrder(0, GXTexCoordID::NONE, GXTexMapID::NONE, GXChannelID::COLOR0A0);

    // Set blend mode
    GXSetBlendMode(GXBlendMode::NONE, GXBlendFactor::ZERO, GXBlendFactor::ZERO, GXLogicOp::NOOP);

    // Load camera matrix
    nw4r::math::MTX34 mtx;
    m3d::getCurrentCamera().GetCameraMtx(&mtx);
    GXLoadPosMtxImm((MTX34*)&mtx, 0);

    // Set line width to 3 pixels and point size to 6 pixels
    GXSetLineWidth(18, GXTexOffset::TO_ZERO);
    GXSetPointSize(36, GXTexOffset::TO_ZERO);

    // Load debug flags from config
    u32 flags = dConfigManager_c::instancePtr->collisionDebugFlags;

    // Draw all instances of dCc_c
    if (flags & (1 << ColliderDisplayFlags::Hitboxes)) {
        dCc_c* currCc = dCc_c::mEntryN;
        while (currCc) {

            // Make sure the actor isn't dead and that its owner exists
            if (currCc->isDead != 2) {

                u32 uptr = (u32)currCc;
                u8 r = (uptr >> 16) & 0xFF;
                u8 g = (uptr >> 8) & 0xFF;
                u8 b = uptr & 0xFF;
                u8 a = 0xFF;

                float centreX = currCc->getCenterPosX();
                float centreY = currCc->getCenterPosY();
                float edgeDistX = currCc->info.xDistToEdge;
                float edgeDistY = currCc->info.yDistToEdge;
                u8 collType = currCc->collisionType;

                // Call DrawCircle for circles
                if (collType == ccCollType::Circle)
                    DrawCircle(centreX, centreY, edgeDistX, edgeDistY, 9000.0f, r, g, b, a);

                // Else call DrawQuad
                else {
                    float tlX, tlY, trX, trY, blX, blY, brX, brY;
                    bool addDiagonal = true;

                    // Use trapezoidDist for Y coordinates if collType is 2
                    // Else edge distance
                    if (collType == ccCollType::TrapezoidUD) {
                        tlY = centreY + currCc->trapezoidDist1;
                        trY = centreY + currCc->trapezoidDist3;
                        blY = centreY + currCc->trapezoidDist2;
                        brY = centreY + currCc->trapezoidDist4;
                        addDiagonal = false;
                    } else {
                        tlY = centreY + edgeDistY;
                        trY = centreY + edgeDistY;
                        blY = centreY - edgeDistY;
                        brY = centreY - edgeDistY;
                    }

                    // Use trapezoidDist for X coordinates if collType is 3
                    // Else edge distance
                    if (collType == ccCollType::TrapezoidLR) {
                        tlX = centreX + currCc->trapezoidDist1;
                        trX = centreX + currCc->trapezoidDist2;
                        blX = centreX + currCc->trapezoidDist3;
                        brX = centreX + currCc->trapezoidDist4;
                        addDiagonal = false;
                    } else {
                        tlX = centreX - edgeDistX;
                        trX = centreX + edgeDistX;
                        blX = centreX - edgeDistX;
                        brX = centreX + edgeDistX;
                    }

                    // Draw the quad
                    DrawQuad(tlX, tlY, trX, trY, blX, blY, brX, brY, 9000.0f, r, g, b, a, addDiagonal);
                }
            }

            currCc = currCc->prev;
        }
    }

    // Draw all instances of dBg_ctr_c
    if (flags & (1 << ColliderDisplayFlags::Colliders)) {
        dBg_ctr_c* currBgCtr = dBg_ctr_c::mEntryN;
        while (currBgCtr) {

            u32 uptr = (u32)currBgCtr;
            u8 r = (uptr >> 16) & 0xFF;
            u8 g = (uptr >> 8) & 0xFF;
            u8 b = uptr & 0xFF;
            u8 a = 0xFF;

            // If round, draw a circle
            if (currBgCtr->isRound)
                DrawCircle(currBgCtr->lastPos.x, currBgCtr->lastPos.y, currBgCtr->radius, currBgCtr->radius, 9000.0f, r, g, b, a);

            // Else draw a quad
            else {
                float tlX = currBgCtr->calcedPos[0].x;
                float tlY = currBgCtr->calcedPos[0].y;
                float trX = currBgCtr->calcedPos[3].x;
                float trY = currBgCtr->calcedPos[3].y;
                float blX = currBgCtr->calcedPos[1].x;
                float blY = currBgCtr->calcedPos[1].y;
                float brX = currBgCtr->calcedPos[2].x;
                float brY = currBgCtr->calcedPos[2].y;
                DrawQuad(tlX, tlY, trX, trY, blX, blY, brX, brY, 9000.0f, r, g, b, a, false);
            }

            currBgCtr = currBgCtr->prev;
        }
    }

    // Draw all instances of dBc_c
    if (flags & (1 << ColliderDisplayFlags::Sensors)) {
        dBc_c* currBc = firstBc;
        while (currBc) {

            // Get the color
            u32 uptr = (u32)currBc;
            u8 r = (uptr >> 16) + 0x20;
            u8 g = (uptr >> 8) + 0x30;
            u8 b = (uptr & 0xFF) + 0x80;
            u8 a = 0xFF;

            // Get the actor's position
            float ownerPosX = currBc->pos->x;
            float ownerPosY = currBc->pos->y;

            // Make an array of sensors
            sensorBase_s* sensors[4] = {currBc->belowSensor, currBc->aboveSensor, currBc->adjacentSensor, currBc->adjacentSensor};

            // Draw the sensors
            for (int i = 0; i < 4; i++) {

                // Check if the sensor exists
                sensorBase_s* sensor = sensors[i];
                if (sensor == NULL)
                    continue;

                // Multiplier for the adjacent sensors
                int mult = (i == 3) ? -1 : 1;
                float x1, y1, x2, y2;
                bool isLine = sensor->flags & 1;

                if (isLine == false) {
                    pointSensor_s* pointSensor = (pointSensor_s*)sensor;

                    x1 = ownerPosX + (float)(mult * pointSensor->x / 4096);
                    y1 = ownerPosY + (float)(pointSensor->y / 4096);

                    DrawPoint(x1, y1, 8005.0f, r, g, b, a);

                } else {
                    lineSensor_s* lineSensor = (lineSensor_s*)sensor;

                    if (i < 2) {
                        x1 = ownerPosX + (float)(lineSensor->lineA / 4096);
                        x2 = ownerPosX + (float)(lineSensor->lineB / 4096);
                        y1 = ownerPosY + (float)(lineSensor->distanceFromCenter / 4096);
                        y2 = ownerPosY + (float)(lineSensor->distanceFromCenter / 4096);
                    } else {
                        x1 = ownerPosX + (float)(mult * lineSensor->distanceFromCenter / 4096);
                        x2 = ownerPosX + (float)(mult * lineSensor->distanceFromCenter / 4096);
                        y1 = ownerPosY + (float)(lineSensor->lineA / 4096);
                        y2 = ownerPosY + (float)(lineSensor->lineB / 4096);
                    }

                    DrawLine(x1, y1, x2, y2, 8005.0f, r, g, b, a);
                }
            }

            currBc = currBc->next;
        }
    }

    // Draw all instances of dRide_ctr_c
    if (flags & (1 << ColliderDisplayFlags::RideableColliders)) {
        dRide_ctr_c* currRide = dRide_ctr_c::mEntryN;
        while (currRide) {

            u32 uptr = (u32)currRide;
            u8 r = (uptr >> 16) & 0xFF;
            u8 g = (uptr >> 8) & 0xFF;
            u8 b = uptr & 0xFF;
            u8 a = 0xFF;

            // For dRide2Point and dRideRoll, draw a simple line
            if (currRide->type <= 2)
                DrawLine(currRide->left.x, currRide->left.y, currRide->right.x, currRide->right.y, 9000.0f, r, g, b, a);

            // dRideCircle is a little bit more complex
            else {
                dRideCircle_c* currCircle = (dRideCircle_c*)currRide;

                // Get centre and radius
                float centreX = currCircle->owner->pos.x + currCircle->centreOffset.x;
                float centreY = currCircle->owner->pos.y + currCircle->centreOffset.y;
                float radius = currCircle->radius;

                // If the circle is full, use the regular circle method
                if (currCircle->leftAngleOffset + currCircle->rightAngleOffset == 0x10000)
                    DrawCircle(centreX, centreY, radius, radius, 9000.0f, r, g, b, a);

                // Else draw a partial circle
                else {
                    u16 minAngle = currCircle->rotation - currCircle->rightAngleOffset;
                    u16 maxAngle = minAngle + currCircle->leftAngleOffset;
                    DrawPartialCircle(centreX, centreY, radius, 9000.0f, minAngle, maxAngle, r, g, b, a);
                }
            }

            currRide = currRide->prev;
        }
    }
}

// Schedule renderer for drawing
kmBranchDefCpp(0x80830BD8, NULL, int, void) {
    instance.entry();
    return 1;
}

// Patches to allow tracking instances of dBc_c
void addBcToList(dBc_c* self) {

    // If the bc was already initialized, bail
    if (self->next || lastBc == self)
        return;

    // If first is NULL, set this bc as both first and last
    if (firstBc == NULL) {
        firstBc = self;
        lastBc = self;

    // Else set the next field of the previous one, and set this one as last
    } else {
        lastBc->next = self;
        lastBc = self;
    }
}

void removeBcFromList(dBc_c* self) {

    // If no bcs are initialized, bail
    if (!firstBc)
        return;

    // If this bc has no "next" and isn't the last bc it was never initialized, so bail
    if (!self->next && lastBc != self)
        return;

    // If this bc is the only initialized one, set both first and last to NULL
    if (firstBc == lastBc) {
        firstBc = NULL;
        lastBc = NULL;
        return;
    }

    // If this bc is the first one, set the next one as the first one
    if (firstBc == self) {
        firstBc = self->next;
        return;
    }

    // Find the previous bc
    dBc_c* prevBc = firstBc;
    while (prevBc->next != self)
        prevBc = prevBc->next;

    // Remove this bc from the list
    prevBc->next = self->next;

    // If this was the last bc, set the previous one as the new last
    if (lastBc == self)
        lastBc = prevBc;
}

// Initialize "next" field to NULL
kmWrite32(0x8006CF50, 0x38800000);

// Add instance to the linked list once initialized
kmCallDefAsm(0x8006D104) {

    // No stack saving needed
    nofralloc

    // Original instruction
    stw r0, 0xE8(r30)

    // Call CPP function
    mr r3, r30
    b addBcToList
}

// Remove instance from the linked list when destroyed
kmCallDefAsm(0x8006CFBC) {

    // Push stack manually
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r4, 0xC(r1)

    // Call CPP function
    bl removeBcFromList

    // Pop stack manually
    lwz r4, 0xC(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10

    // Restore registers
    mr r3, r31
    cmpwi r4, 0
    blr
}
