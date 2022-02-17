#pragma once

#include <kamek.h>
#include <fBase/dBase/dBase.h>

struct FlowerEntry {
    float x, y;
    u8 type;
    // 3 bytes padding
};

class dBg_c : dBase_c {
    public:
        u8 unk[0x8F410]; // TODO: document this properly
        u32 grassCount;
        u32 flowerCount;
        FlowerEntry grassEntries[100];
        FlowerEntry flowerEntries[100];
        // TODO: the rest of the class
};
