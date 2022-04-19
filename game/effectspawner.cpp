#include <kamek.h>
#include "effectspawner.h"

// Build function
dEffectSpawner_c* dEffectSpawner_c::build() {
    return new dEffectSpawner_c;
}

int dEffectSpawner_c::create() {

    // Setup eventFlag (nybbles 5-6)
    u8 eventNum = (this->settings >> 24) & 0xFF;
    this->eventFlag = (u64)1 << (eventNum - 1);

    // Setup scale (nybble 7)
    u16 scale = (this->settings >> 20) & 0xF;
    if (scale == 0)
        scale = 4;
    this->scale = float(scale) / 4.0;

    // Setup effect index (nybbles 10-12)
    this->effect = this->settings & 0xFFF;

    // Setup timer and delay (nybble 9)
    this->timer = 0;
    this->delay = (this->settings >> 12) & 0xF * 60;

    // Setup isGFX (nybble 8 bit 4)
    this->isGFX = (this->settings >> 16) & 1;

    // Setup runOnce
    this->runOnce = (this->delay == 0);
    return 1;
}

int dEffectSpawner_c::execute() {
    // TODO: everything
    return true;
}
