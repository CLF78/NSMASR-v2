#include <kamek.h>
#include <dBgActorManager.h>
#include <dBgGlobal.h>
#include <dRes.h>
#include <profileid.h>
#include <fBase/dBase/dBaseActor/daUnitRail.h>
#include <fBase/dBase/dScene/dScStage.h>
#include <nw4r/math/types.h>
#include <rvl/gx/GXStruct.h>
#include <rvl/mtx/mtx.h>
#include <stdlib/string.h>
#include "tileset/profoverride.h"

// Externs for ASM call
extern "C" {
void DoObjOverride(dBgActorManager_c* mng, char* tileNames);
void DestroyOverrides();
GXColor GetRailColor(daUnitRail_c* rail, u32 originalType, GXColor originalColor);
nw4r::math::VEC2* GetRailTexScale(nw4r::math::VEC2* originalScales, daUnitRail_c* rail);
}

// External data
extern char Rail, RailWhite, RailDaishizen, RailMinigame;
extern dBgActorManager_c::BgObjName_t* OriginalOverrides[5];
extern GXColor RailColors[5];
extern nw4r::math::VEC2 RailScales[5];

void ParseObjOverride(ProfsBin* data, u32 entryCount, dBgActorManager_c::BgObjName_t* buffer, int slot) {

    // Get profileID version
    u8 profileIdVersion = data->profileIDVersion;

    // Parse entries
    for (int i = 0; i < entryCount; i++) {

        // Get current entry
        ProfsBinEntry* currSrc = &data->entries[i];
        dBgActorManager_c::BgObjName_t* currDest = &buffer[i];

        // Copy the tile number
        currDest->tileNum = (0x100 * slot) | currSrc->tileNum;

        // Copy the profile number based on version
        u16 profileId = currSrc->profileID;
        switch(profileIdVersion) {
            case PROFILEKOR:
                if (profileId >= 702)
                    profileId += 2;
                break;
            case PROFILECHN:
                if (profileId >= 621)
                    profileId += 2;
                if (profileId >= 704)
                    profileId += 2;
                break;
        }
        currDest->profileId = profileId;

        // Copy the rest using memcpy
        memcpy(&currDest->xOffs, &currSrc->xOffs, 0x18);

        // Special code for rail actor
        if (profileId == ProfileId::UNIT_RAIL) {
            // Copy tile number in the settings to allow later identification
            currDest->settings |= currDest->tileNum << 16;

            // Store color indexes
            currDest->railColorIndex = currSrc->railColorIndex;
            currDest->railTexSrtIndex = currSrc->railTexSrtIndex;
        }
    }
}

void DoObjOverride(dBgActorManager_c* mng, char* tileNames) {

    // Store pointers to the overrides and their lengths on the stack
    ProfsBin* files[4] = {NULL, NULL, NULL, NULL};
    int lengths[4] = {0, 0, 0, 0};

    // Set up type to 0 and count to 1 (to account for dummy final entry)
    int type = 0;
    u32 count = 1;

    // Initial parsing
    for (int i = 0; i < 4; i++) {

        // Get tileset name
        const char* currTileName = &tileNames[32*i];

        // If not set, go to next tileset
        if (currTileName[0] == '\0')
            continue;

        // Get override file
        ProfsBin* currFile = (ProfsBin*)dResMng_c::instance->res.getRes(currTileName, PROFDATA);

        // Check if file was found and that the version matches
        if (currFile != NULL && currFile->version == PROFSPECVERSION) {

            // Store pointer and entry count
            files[i] = currFile;
            lengths[i] = currFile->numEntries;

        // File not found or invalid, replicate donut lifts
        } else if (i == 0)
            lengths[i] = 1;

        // File not found or invalid, replicate rails
        else if (i == 3) {
            if (!strcmp(currTileName, &Rail)) {
                type = 1;
                lengths[i] = 26;
            } else if (!strcmp(currTileName, &RailWhite)) {
                type = 2;
                lengths[i] = 26;
            } else if (!strcmp(currTileName, &RailDaishizen)) {
                type = 3;
                lengths[i] = 13;
            } else if (!strcmp(currTileName, &RailMinigame)) {
                type = 4;
                lengths[i] = 19;
            }
        }

        // Increase count for later
        count += lengths[i];
    }

    // Set type for rail colors
    mng->type = type;

    // Allocate buffer
    dBgActorManager_c::BgObjName_t* buffer = new dBgActorManager_c::BgObjName_t[count];

    // Counter to keep track of parsed entries
    int parsedCount = 0;

    // Parse the entries
    for (int i = 0; i < 4; i++) {

        // Failsafe for empty files
        if (lengths[i]) {

            // If file was found, let the parser deal with it
            if (files[i] != NULL) {
                ParseObjOverride(files[i], lengths[i], &buffer[parsedCount], i);

            // Else if slot is Pa0, copy the donut lifts override
            } else if (i == 0)
                memcpy(&buffer[parsedCount], &OriginalOverrides[0][0], sizeof(dBgActorManager_c::BgObjName_t));

            // Else if slot is Pa3 and type is set, copy the corresponding rail overrides
            else if (i == 3 && type != 0)
                memcpy(&buffer[parsedCount], &OriginalOverrides[type][1], lengths[i] * sizeof(dBgActorManager_c::BgObjName_t));
            }

        // Increase counter
        parsedCount += lengths[i];

    }

    // Set dummy final entry
    buffer[parsedCount].profileId = ProfileId::DUMMY_ACTOR;

    // Store array to static address
    dBgActorManager_c::bgObjNameList = buffer;
}

void DestroyOverrides() {
    // Delete allocated overrides
    delete dBgActorManager_c::bgObjNameList;
}

// Helper function
dBgActorManager_c::BgObjName_t* GetBgObjFromRail(daUnitRail_c* rail) {

    // Grab tilenum from settings
    u16 tileNum = rail->settings >> 16;

    // Get bgActorObj entry by tileNum
    dBgActorManager_c::BgObjName_t* currEntry = &dBgActorManager_c::bgObjNameList[0];
    while(currEntry->profileId != ProfileId::DUMMY_ACTOR) {
        if (currEntry->profileId == ProfileId::UNIT_RAIL && currEntry->settings >> 16 == tileNum)
            break;
        currEntry++;
    }

    return currEntry;
}

GXColor GetRailColor(daUnitRail_c* rail, GXColor originalColor) {

    // Get bgObj from rail
    dBgActorManager_c::BgObjName_t* bgObj = GetBgObjFromRail(rail);

    // Check rail settings
    u8 colorIndex = (bgObj->railColorIndex);

    if (colorIndex == 0)
        return originalColor;

    else if (colorIndex < 5)
        return RailColors[colorIndex];

    // Get tileset slot
    u8 slot = rail->settings >> 24;

    // Get override file (failsaves not needed)
    char* tilesetName = dBgGlobal_c::instance->getEnvironment(dScStage_c::m_instance->currentArea, slot);
    ProfsBin* bin = (ProfsBin*)dResMng_c::instance->res.getRes(tilesetName, PROFDATA);

    // Go to color table
    GXColor* table = (GXColor*)((u32)&bin->entries + (bin->numEntries * sizeof(ProfsBinEntry)));

    // Get the color according to the index given
    return table[colorIndex - 5];

}

nw4r::math::VEC2* GetRailTexScale(nw4r::math::VEC2* originalScales, daUnitRail_c* rail) {

    // Get bgObj from rail
    dBgActorManager_c::BgObjName_t* bgObj = GetBgObjFromRail(rail);

    // Check rail settings
    u8 texSrtIndex = (bgObj->railTexSrtIndex);

    if (texSrtIndex == 0)
        return originalScales;

    else if (texSrtIndex < 5)
        return &RailScales[texSrtIndex];

    // Get tileset slot
    u8 slot = rail->settings >> 24;

    // Get override file (failsaves not needed)
    char* tilesetName = dBgGlobal_c::instance->getEnvironment(dScStage_c::m_instance->currentArea, slot);
    ProfsBin* bin = (ProfsBin*)dResMng_c::instance->res.getRes(tilesetName, PROFDATA);

    // Go to scale table
    nw4r::math::VEC2* table = (nw4r::math::VEC2*)((u32)&bin->entries + (bin->numEntries * sizeof(ProfsBinEntry)) + bin->numColors * sizeof(GXColor));

    // Get the scale according to the index given
    return &table[texSrtIndex - 5];
}

// Force rails to be loaded by default
kmWrite32(0x8091FCC4, 0x48000058);
kmWritePointer(0x8098C464, "rail");

kmBranchDefAsm(0x8007E30C, 0x8007E3AC) {

    // No stack saving necessary here
    nofralloc

    // If there are no zones, bail
    cmpwi r3, 0
    beq end

    // Setup call + modified original instruction
    lwz r4, 0x8(r3)
    mr r3, r29
    bl DoObjOverride

    // Return later to skip all the Nintendo fluff
    end:
    blr
}

kmBranchDefAsm(0x8007E270, 0x8007E274) {
    // No need for stack saving
    nofralloc

    // Call destroyer
    bl DestroyOverrides

    // Original instruction
    li r0, 0
    blr
}

kmBranchDefAsm(0x808B2A40, 0x808B2A44) {
    // Let me free
    nofralloc

    // Call C++ function
    addi r4, r6, 4
    bl GetRailColor

    // Move color to r0
    mr r0, r3

    // Restore registers and return
    mr r3, r29
    li r4, 1
    addi r5, r1, 0xC
    blr
}

kmCallDefAsm(0x808B2AE0) {
    // Let me free
    nofralloc

    // Original instruction
    add r3, r3, r0

    // Push stack manually
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)

    // Save r5
    stw r5, 0xC(r1)

    // Call CPP function
    addi r3, r3, 0x2C
    mr r4, r29
    bl GetRailTexScale

    // Subtract from offset to fit the original instructions
    subi r3, r3, 0x2C

    // Restore r5
    lwz r5, 0xC(r1)

    // Pop stack manually and return
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
