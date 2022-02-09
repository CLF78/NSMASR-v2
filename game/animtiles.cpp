#include <kamek.h>
#include <dBgGlobal.h>
#include <dBgTexMng.h>
#include <dRes.h>
#include <fBase/dBase/dScene/dScStage.h>
#include <stdlib/stdio.h>
#include "animtiles.h"

void ProcessAnimsBin(dBgTexMng_c* mng, AnimsBin* animMeta, int slot, char* tileName) {
    char buffer[32];

    for (int i = 0; i < animMeta->numEntries; i++) {
        // Print name to buffer
        snprintf(buffer, sizeof(buffer), ANIMTILE, i);

        // Get relevant anim entry and framesheet
        AnimsBinEntry* currAnim = &animMeta->entries[i];
        u8* currAnimDelays = (u8*)((u32)animMeta + currAnim->delayOffs);

        // Setup the animated tile (function takes care of everything)
        mng->setupAnimTile(slot, currAnim->tileNum, buffer, currAnimDelays, currAnim->reverse);
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

        // If tileset is null, skip
        if (!tileName || tileName[0] == '\0')
            continue;

        // Get anims.bin from relevant file
        AnimsBin* animMeta = (AnimsBin*)dResMng_c::instance->res.getRes(tileName, ANIMMETA);

        // If file was not found or the version mismatches, skip
        if (!animMeta || animMeta->version != SPECVERSION)
            continue;

        // Process anims file
        ProcessAnimsBin(mng, animMeta, slot, tileName);
    }
}
