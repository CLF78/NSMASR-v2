#pragma once

#include <kamek.h>
#include <m/mHeapAllocator.h>
#include <rvl/mtx/mtx.h>

class dBgActorManager_c {
    public:
        class BgObj_c {
            public:
                u16 uniqueId;
                u16 x, y;
                u8 layer;
                // 1 byte padding
                u32 profileId;
        };

        void* vtable;
        mHeapAllocator_c allocator;
        VEC3 screenBL;
        VEC3 screenTR;
        BgObj_c* objects;
        int count;
        int type;

        struct BgObjName_t {
            u32 tileNum;
            u16 profileId;
            u8 railColorIndex; // custom field, byte unused by game
            u8 railTexSrtIndex; // custom field, byte unused by game
            float xOffs, yOffs, zOffs;
            float xScale, yScale;
            u32 settings;
        };

        static BgObjName_t* bgObjNameList; // unofficial name

};
