#include <kamek.h>
#include <dBgGlobal.h>
#include <dBgTexMng.h>
#include <dRes.h>
#include <fBase/dBase/dScene/dScStage.h>
#include <stdlib/stdio.h>
#include "tileset/anim.h"

// Define for common.cpp
#define ANIMCPP

// Process animation data
void ProcessAnimsBin(dBgTexMng_c* mng, AnimsBin* animData, int slot, char* tileName) {
    char buffer[32];

    for (int i = 0; i < animData->numEntries; i++) {
        // Get relevant anim entry and framesheet
        AnimsBinEntry* currAnim = &animData->entries[i];
        u8* currAnimDelays = (u8*)((u32)animData + currAnim->delayOffs);

        // Print name to buffer
        snprintf(buffer, sizeof(buffer), ANIMTILE, currAnim->tileNum);

        // Setup the animated tile (function takes care of everything)
        mng->setupAnimTile(slot, 0x100 * slot | currAnim->tileNum, buffer, currAnimDelays, currAnim->reverse);
    }
}

// Expand tileset allocation (original value = 0x400; is this even necessary?)
kmWrite16(0x80087546, 0x1000);

// Actual animtiles code
kmCallDefCpp(0x80087840, void, dBgTexMng_c* mng, int slot, u16 tileNum, char* name, u8* pFrameTimes, bool reverse) {

    // Original call that we hijacked
    mng->setupAnimTile(slot, tileNum, name, pFrameTimes, reverse);

    // Get current area
    int area = dScStage_c::m_instance->currentArea;

    // Process every slot
    for (slot = 0; slot < 4; slot++) {
        // Get the tileset name
        char* tileName = dBgGlobal_c::instance->getEnvironment(area, slot);

        // If tileset isn't set, skip
        if (tileName[0] == '\0')
            continue;

        // Get anims.bin from relevant file
        AnimsBin* animData = (AnimsBin*)dResMng_c::instance->res.getRes(tileName, ANIMDATA);

        // If file was not found or the version mismatches, skip
        if (animData == NULL || animData->version != ANIMSPECVERSION)
            continue;

        // Process anims file
        ProcessAnimsBin(mng, animData, slot, tileName);
    }
}
