#pragma once

#include <kamek.h>

enum WaterType {
    WATER = 0,
    LAVA = 1,
    POISON = 2,
    ROUND_BUBBLE = 3,
    TALL_BUBBLE = 4,
    WIDE_BUBBLE = 5,
};

class dWaterEntry_c {
    public:
        float x, y, z;
        float width, height;
        int isInUse;
        u8 type;
        u8 layer;
        // 2 bytes padding
};

class dWaterEntryMng_c {
    public:
        dWaterEntry_c entries[80];
        float currentStrength; // set by the unused water current sprite
};
