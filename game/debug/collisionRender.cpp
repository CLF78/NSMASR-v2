#include <kamek.h>
#include <dBc.h>
#include <dCc.h>
#include <m/m3d/camera.h>
#include <nw4r/g3d/camera.h>
#include <rvl/gx/GXBump.h>
#include <rvl/gx/GXCull.h>
#include <rvl/gx/GXEnum.h>
#include <rvl/gx/GXGeometry.h>
#include <rvl/gx/GXLighting.h>
#include <rvl/gx/GXPixel.h>
#include <rvl/gx/GXStruct.h>
#include <rvl/gx/GXTev.h>
#include <rvl/gx/GXTransform.h>
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
