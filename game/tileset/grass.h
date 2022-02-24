#pragma once

#include <kamek.h>

#define GRASSDATA "BG_grass/grass_overrides.bin"
#define GRASSSPECVERSION 1
#define FLOWERFILE "obj_hana_custom"
#define GRASSFILE "obj_kusa_custom"
#define BRRESFMT "g3d/t%02d.brres"

// Define for common.cpp
#define GRASSCPP

struct GrassBinEntry {
    u8 tileNum;
    u8 flowerValue:4;  // 0 = pink, 1 = yellow, 2 = blue, 3-4 = custom, any other value = none
    u8 grassValue:4;   // 0 = left edge, 1-3 = middles, 4 = right edge, any other value = none
};

struct GrassBin {
    u8 version;      // currently 1
    u8 flowerStyle;  // 0 = nohara, 1 = daishizen, 2+ = custom
    u8 grassStyle;   // 0 = nohara, 1 = nohara again, 2+ = custom
    // (note: no padding here!)
    GrassBinEntry entries[];
};

// Helper class for extra data that needs to be saved
class dGrassBinMng_c {
    public:
        dGrassBinMng_c(GrassBin* rawData, u8 numTiles, u8 slot);
        ~dGrassBinMng_c();

        GrassBinEntry* getFlowerData(u16 tileNum);

        GrassBin* data;
        u8 numEntries;
        u8 tileSlot;

        static dGrassBinMng_c* instance;
        static dGrassBinMng_c* build(GrassBin* rawData, u8 numTiles, u8 slot);
};
