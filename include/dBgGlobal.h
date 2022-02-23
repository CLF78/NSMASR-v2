#pragma once

#include <kamek.h>
#include <egg/eggFrmHeap.h>

typedef struct {
    u16 offset;
    u8 width;
    u8 height;
} HeadDataEntry;

class dBgGlobal_c {
    public:
        void* vtable;
        u8* bgDatas[4][3];
        u8* tileMaps[4][3]; // actually dBgUnit_c
        HeadDataEntry* unitHeadDatas[4][4];
        u8* unitDatas[4][4];
        char tilesetNames[4][4][32];
        EGG::FrmHeap* heaps[4][4];
        u32 _324;

        char* getEnvironment(int area, int tileSlot);

        static dBgGlobal_c* instance;
};
