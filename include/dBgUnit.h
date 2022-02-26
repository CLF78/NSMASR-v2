#pragma once

#include <kamek.h>
#include <egg/eggFrmHeap.h>

// Documentation by Ninji

struct BGRender {
    u8 unk[0xC00];
    u8 *objData;
    u8 _C04, _C05; // extracted from UnitHeadData, maybe row and column?
    u16 _C06, _C08; // unused??
    u16 blockNumber;
    u16 currX, currY;
    u16 currTile;
    u16 objDataOffset, objType, objX, objY, objWidth, objHeight;
    u16 tileNumberWithinBlock, areaID;
};

struct BGBuffer {
    u16 tiles[0x100];
};

class dBgUnit_c {
    public:
        void* vtable;
        BGBuffer* allocatedBlocks[256];
        u32 _404;
        u8 usedIDs[2048];
        u16 nextID;
        // 2 bytes padding
        u32 pa0_id, pa1_id, pa2_id, pa3_id; // only set for Nintendo tilesets and used for randomization
        u32 layerId, areaId;
        EGG::FrmHeap* heap;
        bool isNot2CastleA1;
        // 3 bytes padding

        u16* getTileP(u32 x, u32 y, u32* block, bool placeTile); // last param is unused

        void generateTile(BGRender* render, u16* tileArray, int arrayLength, int slot);
        void generateHorizontalTile(BGRender* render, u16* tileArray, int arrayLength, int slot);
        void generateVerticalTile(BGRender* render, u16* tileArray, int arrayLength, int slot);

        static dBgUnit_c* create(dBgUnit_c* unit, EGG::Heap* heap, int area, int layer);
};
