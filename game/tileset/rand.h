#pragma once

#include <kamek.h>

#define RANDDATA "BG_rand/randtiles.bin"
#define RANDSPECVERSION 1

// Define for common.cpp
#define RANDCPP

enum NormalType {
    NONE,
    HORZ,
    VERT,
    BOTH
};

enum SpecialType {
    NONE_SPECIAL,
    VDOUBLE_TOP,
    VDOUBLE_BOTTOM,
    HDOUBLE_LEFT,
    HDOUBLE_RIGHT
};

struct RandTileBinEntry {
    u8 tile; // tile to be randomized
    u8 normalType; // 0 = none, 1 = horizontal only, 2 = vertical only, 3 = both directions
    u8 specialType; // 0 = none, 1 = vertical double top, 2 = vertical double bottom, 3 = horizontal double left, 4 = horizontal double right
    u8 arrayLen; // length of tile list, due to the possibility of tiles being 00
    u32 tileArrayOffs; // offset to tile list in u16 format, relative to start of file
};

struct RandTileBin {
    u8 version;
    u8 numEntries;
    // 2 bytes padding
    RandTileBinEntry entries[];
};

class dRandTileMng_c {
    public:
        dRandTileMng_c(int area);
        ~dRandTileMng_c();

        RandTileBin* randData[4];

        static dRandTileMng_c* instance;
        static dRandTileMng_c* build(int area);
};
