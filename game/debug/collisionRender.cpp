#include <kamek.h>
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
