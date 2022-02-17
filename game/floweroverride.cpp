#include <kamek.h>
#include <fBase/dBase/dScene/dScStage.h>
#include <dBgGlobal.h>
#include <dRes.h>
#include "floweroverride.h"

// Externs for ASM calls
extern "C" {
void LoadGrassBin();
bool AreCustomFlowersLoaded();
}

// Static instance
dGrassBinMng_c* dGrassBinMng_c::instance = NULL;

// Build function
dGrassBinMng_c* dGrassBinMng_c::build(GrassBin* rawData, u8 numTiles, u8 slot) {

    // If an instance is already initialized, return it
    if (dGrassBinMng_c::instance != NULL)
        return dGrassBinMng_c::instance;

    // Create class and return it
    return new dGrassBinMng_c(rawData, numTiles, slot);
}

// Constructor
dGrassBinMng_c::dGrassBinMng_c(GrassBin* rawData, u8 numTiles, u8 slot) {

    // Set variables
    this->data = rawData;
    this->numEntries = numTiles;
    this->tileSlot = slot;

    // Set static instance
    dGrassBinMng_c::instance = this;
}

// Destructor
dGrassBinMng_c::~dGrassBinMng_c() {

    // Reset static instance
    dGrassBinMng_c::instance = NULL;
}

void LoadGrassBin() {

    // Allocate length on the stack
    u32 length;

    // Process each tileset, excluding Pa0
    for (int slot = 1; slot < 4; slot++) {

        // Get tileset name
        const char* tileName = dBgGlobal_c::instance->getEnvironment(dScStage_c::m_instance->currentArea, slot);

        // If tileset is null, skip
        if (tileName[0] == '\0')
            continue;

        // Get the grass file
        GrassBin* bin = (GrassBin*)dResMng_c::instance->res.getRes(tileName, OVERRIDEFILE, &length);

        // If the file was not found or is invalid, skip it
        if (bin == NULL || length == 0 || bin->version != SPECVERSION)
            continue;

        // Otherwise build the class and return
        dGrassBinMng_c::build(bin, (length-3) / sizeof(GrassBinEntry), slot);
        return;
    }
}

bool AreCustomFlowersLoaded() {
    return (dGrassBinMng_c::instance != NULL);
}

// Load custom flower/grass files at boot (replaces checkered spring blocks and ledge donuts)
kmWritePointer(0x8098C488, CUSTOMFLOWERFILE);
kmWritePointer(0x8098C490, CUSTOMGRASSFILE);

// Preload flower data so we can reuse it anytime in the level
kmCallDefAsm(0x801548FC) {

    // Call function
    bl LoadGrassBin

    // Original instruction
    mr r3, r30
}

// Hijack the function end to destroy the flower data
kmBranchDefCpp(0x80154E84, NULL, int, void) {
    delete dGrassBinMng_c::instance;
    return 1;
}

kmCallDefAsm(0x80077F88) {
    // Prevent register restoring
    nofralloc

    // Push stack manually (preserve r0)
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)

    // Check if flowers were loaded
    bl AreCustomFlowersLoaded

    // Move result to r29 and restore r0
    mr r29, r3
    lbz r0, 0(r26)

    // Check result
    cmpwi r3, 0
    beq end

    // If result is 1, automatically set first character of string to 0 to skip the string checks
    li r0, 0

    // Restore r3 and execute original instruction
    end:
    mr r3, r26
    extsh. r0, r0

    // Pop stack manually and return
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
