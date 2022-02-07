#include <kamek.h>
#include <dBgGlobal.h>
#include <dRes.h>

// Head data size to be used in the FixTilesetSlot function
static u32 hdSize;

// Extern for ASM function
extern "C" {
void FixTilesetSlot(u8* data, HeadDataEntry* hd, int tileSlot);
}

// Parser copied from NewerSMBW
void FixUnit(u8* data, int tileSlot) {

    // 0xFF = end of file
    while (*data != 0xFF) {

        // Get command
        u8 cmd = *data;

        // If end of row or slope, go to next byte
        if (cmd == 0xFE || (cmd & 0x80) != 0) {
            data++;
            continue;
        }

        // Clear slot data and set correct slot if the tile is not the Pa0 null tile
        if (data[1] != 0 && (data[2] & 3) != 0) {
            data[2] &= 0xFC;
            data[2] |= tileSlot;
        }

        // Go to next tile
        data += 3;
    }
}

void FixTilesetSlot(u8* unitData, HeadDataEntry* hd, int tileSlot) {
    // Failsaves (tileset has been defined, otherwise we wouldn't be here)
    if (unitData == NULL || hd == NULL || hdSize == 0)
        return;

    // Calculate hd length
    HeadDataEntry* hdEnd = hd + (hdSize / sizeof(HeadDataEntry));

    // Fix each unit by parsing HeadData
    for (HeadDataEntry* currHd = hd; currHd < hdEnd; currHd++)
        FixUnit(unitData + currHd->offset, tileSlot);

    // Reset static variable for next iteration
    hdSize = 0;
}

// Replace call to keep file size available
kmCallDefCpp(0x8008160C, void, dRes_c* res, const char* tilesetName, const char* hdName) {
    res->getRes(tilesetName, hdName, &hdSize);
}

// ASM trampoline for CPP call
kmCallDefAsm(0x80081658) {
    // Original instruction
    stw r3, 0xA4(r27)

    // Setup function call
    // r3 already set
    lwz r4, 0x64(r27)
    mr r5, r24
    bl FixTilesetSlot
}
