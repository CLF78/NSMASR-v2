#include <kamek.h>
#include <fBase/dBase/dBaseActor/dActor/dActor.h>
#include <rvl/gx/GXEnum.h>
#include <rvl/gx/GXGeometry.h>
#include <rvl/gx/GXLighting.h>
#include <rvl/gx/GXStruct.h>
#include <rvl/gx/GXTev.h>
#include <rvl/gx/GXVert.h>
#include <dBc.h>
#include <dCc.h>
#include "debug/collisionRender.h"

static dCollisionRenderProc_c instance;

dCollisionRenderProc_c::dCollisionRenderProc_c() {
    this->create(NULL, NULL);
}

// Dummy function
void dCollisionRenderProc_c::drawOpa() {
}

// Actual drawing
void dCollisionRenderProc_c::drawXlu() {

    // Set current vertex descriptor to enable position and color0, both provided directly
    GXClearVtxDesc();
    GXSetVtxDesc(GXAttr::POS, GXAttrType::DIRECT);
    GXSetVtxDesc(GXAttr::CLR0, GXAttrType::DIRECT);

    // Position has 3 elements (x,y,z), each of type f32
    GXSetVtxAttrFmt(0, GXAttr::POS, GXCompCnt::POS_XYZ, GXCompType::F32, 0);

    // Color 0 has 4 components (r, g, b, a), each of type u8
    GXSetVtxAttrFmt(0, GXAttr::CLR0, GXCompCnt::CLR_RGBA, GXCompType::RGBA8, 0);

    // Enable color channel 0 and set vertex color as source
    GXSetNumChans(1);
    GXSetChanCtrl(GXChannelID::COLOR0A0, false, GXColorSrc::VTX, GXColorSrc::VTX, GXLightID::NONE, GXDiffuseFn::OFF, GXAttnFn::NONE);

    // Enable one TEV stage
    GXSetNumTevStages(1);
    GXSetTevOp(0, GXTevMode::PASSCLR);

    // Set line width to 3 pixels
    GXSetLineWidth(18, GXTexOffset::TO_ZERO);

    dCc_c* currCc = dCc_c::mEntryN;
    while (currCc) {

        u32 uptr = (u32)currCc;
        u8 r = (uptr >> 16) & 0xFF;
        u8 g = (uptr >> 8) & 0xFF;
        u8 b = uptr & 0xFF;
        u8 a = 0xFF;

        // Make sure the actor isn't dead and that its owner exists
        if (currCc->isDead != 2 && currCc->owner != nullptr) {

            GXBegin(GXPrimitive::LINES, 0, 8);

            float centreX = currCc->owner->pos.x + currCc->info.xDistToCenter;
            float centreY = currCc->owner->pos.y + currCc->info.yDistToCenter;
            float edgeDistX = currCc->info.xDistToEdge;
            float edgeDistY = currCc->info.yDistToEdge;

            float tlX = centreX - edgeDistX, tlY = centreY + edgeDistY;
            float trX = centreX + edgeDistX, trY = centreY + edgeDistY;

            float blX = centreX - edgeDistX, blY = centreY - edgeDistY;
            float brX = centreX + edgeDistX, brY = centreY - edgeDistY;

            switch (currCc->collisionType) {
                case 2: // vert trapezoid
                    tlY = centreY + currCc->trapezoidDistTL;
                    trY = centreY + currCc->trapezoidDistTR;
                    blY = centreY + currCc->trapezoidDistBL;
                    brY = centreY + currCc->trapezoidDistBR;
                    break;
                case 3: // horz trapezoid
                    tlX = centreX + currCc->trapezoidDistTL;
                    trX = centreX + currCc->trapezoidDistTR;
                    blX = centreX + currCc->trapezoidDistBL;
                    brX = centreX + currCc->trapezoidDistBR;
                    break;
            }

            // Top
            GXPosition3f32(tlX, tlY, 9000.0f);
            GXColor4u8(r,g,b,a);
            GXPosition3f32(trX, trY, 9000.0f);
            GXColor4u8(r,g,b,a);

            // Left
            GXPosition3f32(tlX, tlY, 9000.0f);
            GXColor4u8(r,g,b,a);
            GXPosition3f32(blX, blY, 9000.0f);
            GXColor4u8(r,g,b,a);

            // Right
            GXPosition3f32(trX, trY, 9000.0f);
            GXColor4u8(r,g,b,a);
            GXPosition3f32(brX, brY, 9000.0f);
            GXColor4u8(r,g,b,a);

            // Bottom
            GXPosition3f32(blX, blY, 9000.0f);
            GXColor4u8(r,g,b,a);
            GXPosition3f32(brX, brY, 9000.0f);
            GXColor4u8(r,g,b,a);

            GXEnd();
        }

        currCc = currCc->prev;
    }
}

// Schedule renderer for drawing
kmBranchDefCpp(0x80830BD8, NULL, int, void) {
    instance.entry();
    return 1;
}

// Patches to allow tracking instances of dBc_c
static dBc_c* firstBc = NULL;
static dBc_c* lastBc = NULL;

extern "C" {
void addBcToList(dBc_c* self);
void removeBcFromList(dBc_c* self);
}

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
