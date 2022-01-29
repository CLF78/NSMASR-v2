#pragma once
#include <kamek.h>
#include <egg/eggHeap.h>
#include "kamekLoader.h"

#define REGION_P 0
#define REGION_E 1
#define REGION_J 2
#define REGION_K 3
#define REGION_W 4

typedef void *(*EGG_Heap_Alloc_t) (u32 size, s32 align, EGG::Heap* heap);
typedef void (*EGG_Heap_Free_t) (void *buffer, EGG::Heap* heap);
typedef void (*memmove_t) (void* dest, const void* src, size_t num);

struct regionData {
	u16 region;
	u16 version;
};

struct loaderFunctionsEx {
	loaderFunctions base;
	EGG_Heap_Alloc_t eggAlloc;
	EGG_Heap_Free_t eggFree;
	EGG::Heap** gameHeaps; // Actually in the mHeap namespace
	EGG::Heap** archiveHeap; // Actually in the mHeap namespace
	memmove_t memmove;
	u32* bcaCheck;
	u32* gameInitTable;
	u8 identifier;
};
