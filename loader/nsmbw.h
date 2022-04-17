#pragma once
#include <kamek.h>
#include <egg/core/eggExpHeap.h>
#include "kamekLoader.h"

#define REGION_P 0
#define REGION_E 1
#define REGION_J 2
#define REGION_K 3
#define REGION_W 4

typedef void *(*EGG_Heap_Alloc_t) (u32 size, s32 align, EGG::Heap* heap);
typedef void (*EGG_Heap_Free_t) (void *buffer, EGG::Heap* heap);

struct regionData {
    u16 region;
    u16 version;
};

struct loaderFunctionsEx {
    loaderFunctions base;
    EGG_Heap_Alloc_t eggAlloc;
    EGG_Heap_Free_t eggFree;
    EGG::ExpHeap** dylinkHeap; // Actually in the mHeap namespace
    EGG::ExpHeap** archiveHeap; // Actually in the mHeap namespace
    u32* bcaCheck;
    u32* gameInitTable;
    u32* arenaFix;
    u8 identifier;
};
