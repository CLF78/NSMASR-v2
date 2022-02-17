#include <kamek.h>
#include <fBase/dBase/dScene/dScStage.h>
#include <dBgGlobal.h>
#include <dBg.h>
#include <dRes.h>
#include "floweroverride.h"

// Externs for ASM calls
extern "C" {
void LoadGrassBin();
bool AreCustomFlowersLoaded();
int AddFlowerEntry(dBg_c* bg, u16 tileNum, u32 x, u32 y);
}

// Static instance (and a pointer to it for ASM because the compiler is garbage)
dGrassBinMng_c* dGrassBinMng_c::instance;
extern "C" {dGrassBinMng_c** instancePtr = &dGrassBinMng_c::instance;}

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

// Get flower data from tile
GrassBinEntry* dGrassBinMng_c::getFlowerData(u16 tileNum) {

    // Traverse through all entries
    for (int i = 0; i < this->numEntries; i++) {

        // Get entry
        GrassBinEntry* current = &this->data->entries[i];

        // Check if tile number matches, and if so return this entry
        if (tileNum == (current->tileNum | 0x100 * this->tileSlot))
            return current;
    }

    // None found, return NULL
    return NULL;
}

void LoadGrassBin() {

    // Allocate length on the stack
    u32 length;

    // Process each tileset
    for (int slot = 0; slot < 4; slot++) {

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

int AddFlowerEntry(dBg_c* bg, u16 tileNum, u32 x, u32 y) {

    // Get the flower data for this tile
    GrassBinEntry* data = dGrassBinMng_c::instance->getFlowerData(tileNum);

    // If none is found, it's just a regular tile, ignore it
    if (data == NULL)
        return tileNum;

    // Setup flower if it was enabled and that we can allocate one
    if (data->flowerValue <= 4 && bg->flowerCount < 99) {
        FlowerEntry* flower = &bg->flowerEntries[bg->flowerCount];
        flower->x = float(x);
        flower->y = -float(y);
        flower->type = data->flowerValue;
        bg->flowerCount++;
    }

    // Setup bush if it was enabled and that we can allocate one
    if (data->grassValue <= 4 && bg->grassCount < 99) {
        FlowerEntry* grass = &bg->grassEntries[bg->grassCount];
        grass->x = float(x);
        grass->y = -float(y);
        grass->type = data->grassValue;
        bg->grassCount++;
    }

    // Return null tile so it doesn't get drawn
    return 0;
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

// Dehardcode tileset name check
kmCallDefAsm(0x80077F88) {
    // Prevent register restoring
    nofralloc

    // Push stack manually
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

// Dehardcode tile position checks - trampoline
kmCallDefAsm(0x8007803C) {

    // Prevent register restoring
    nofralloc

    // Original instruction
    addis r3, r6, 1

    // If dGrassBinMng is not initialized, fall back to Nintendo's code
    lis r4, instancePtr@ha
    lwz r4, instancePtr@l(r4)
    lwz r4, 0(r4)
    cmpwi r4, 0
    beqlr+

    // Push stack manually
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)

    // Call the C++ function
    mr r3, r22
    mr r4, r6
    addi r5, r25, 0x10
    addi r6, r26, 0x8
    bl AddFlowerEntry

    // Move result to r6
    mr r6, r3

    // Pop stack and return (later)
    lwz r12, 0x14(r1)
    addi r12, r12, 0x1AC
    mtlr r12
    addi r1, r1, 0x10
    blr
}
