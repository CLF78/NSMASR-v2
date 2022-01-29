#include <kamek.h>
#include <stdlib/string.h>
#include <egg/eggHeap.h>
#include "kamekLoader.h"
#include "nsmbw.h"

void *allocAdapter(u32 size, bool isForCode, const loaderFunctions *funcs) {
	const loaderFunctionsEx *funcsEx = (const loaderFunctionsEx *)funcs;
	EGG::Heap** heapPtr = isForCode ? funcsEx->gameHeaps : funcsEx->archiveHeap;
	return funcsEx->eggAlloc(size, 0x20, *heapPtr);
}

void freeAdapter(void *buffer, bool isForCode, const loaderFunctions *funcs) {
	const loaderFunctionsEx *funcsEx = (const loaderFunctionsEx *)funcs;
	EGG::Heap** heapPtr = isForCode ? funcsEx->gameHeaps : funcsEx->archiveHeap;
	funcsEx->eggFree(buffer, *heapPtr);
}

const loaderFunctionsEx functions[5] = {
	{{(OSReport_t) 0x8015F870,
	(OSFatal_t) 0x801AF710,
	(DVDConvertPathToEntrynum_t) 0x801CA7C0,
	(DVDFastOpen_t) 0x801CAAD0,
	(DVDReadPrio_t) 0x801CAC60,
	(DVDClose_t) 0x801CAB40,
	(sprintf_t) 0x802E1ACC,
	allocAdapter,
	freeAdapter},
	(EGG_Heap_Alloc_t) 0x802B8E00,
	(EGG_Heap_Free_t) 0x802B90B0,
	(EGG::Heap**) 0x80377F48,
	(EGG::Heap**) 0x8042A72C,
	(memmove_t) 0x802DF264,
	(u32*) 0x800CA0B8,
	(u32*) 0x80328428,
	'P'},

	{{(OSReport_t) 0x8015F730,
	(OSFatal_t) 0x801AF5D0,
	(DVDConvertPathToEntrynum_t) 0x801CA680,
	(DVDFastOpen_t) 0x801CA990,
	(DVDReadPrio_t) 0x801CAB20,
	(DVDClose_t) 0x801CAA00,
	(sprintf_t) 0x802E17DC,
	allocAdapter,
	freeAdapter},
	(EGG_Heap_Alloc_t) 0x802B8CC0,
	(EGG_Heap_Free_t) 0x802B8F70,
	(EGG::Heap**) 0x80377C48,
	(EGG::Heap**) 0x8042A44C,
	(memmove_t) 0x802DEF74,
	(u32*) 0x800C9FC8,
	(u32*) 0x803280E0,
	'E'},

	{{(OSReport_t) 0x8015F540,
	(OSFatal_t) 0x801AF3E0,
	(DVDConvertPathToEntrynum_t) 0x801CA490,
	(DVDFastOpen_t) 0x801CA7A0,
	(DVDReadPrio_t) 0x801CA930,
	(DVDClose_t) 0x801CA810,
	(sprintf_t) 0x802E15EC,
	allocAdapter,
	freeAdapter},
	(EGG_Heap_Alloc_t) 0x802B8AD0,
	(EGG_Heap_Free_t) 0x802B8D80,
	(EGG::Heap**) 0x803779C8,
	(EGG::Heap**) 0x8042A16C,
	(memmove_t) 0x802DED84,
	(u32*) 0x800C9F48,
	(u32*) 0x80327E48,
	'J'},

	{{(OSReport_t) 0x8015FC70,
	(OSFatal_t) 0x801AFB10,
	(DVDConvertPathToEntrynum_t) 0x801CABC0,
	(DVDFastOpen_t) 0x801CAED0,
	(DVDReadPrio_t) 0x801CB060,
	(DVDClose_t) 0x801CAF40,
	(sprintf_t) 0x802E1D1C,
	allocAdapter,
	freeAdapter},
	(EGG_Heap_Alloc_t) 0x802B9200,
	(EGG_Heap_Free_t) 0x802B94B0,
	(EGG::Heap**) 0x80384948,
	(EGG::Heap**) 0x804370EC,
	(memmove_t) 0x802DF4B4,
	(u32*) 0x800CA0D8,
	(u32*) 0x80334E10,
	'K'},

	{{(OSReport_t) 0x8015FC70,
	(OSFatal_t) 0x801AFB10,
	(DVDConvertPathToEntrynum_t) 0x801CABC0,
	(DVDFastOpen_t) 0x801CAED0,
	(DVDReadPrio_t) 0x801CB060,
	(DVDClose_t) 0x801CAF40,
	(sprintf_t) 0x802E1D1C,
	allocAdapter,
	freeAdapter},
	(EGG_Heap_Alloc_t) 0x802B9200,
	(EGG_Heap_Free_t) 0x802B94B0,
	(EGG::Heap**) 0x80382D48,
	(EGG::Heap**) 0x804354EC,
	(memmove_t) 0x802DF4B4,
	(u32*) 0x800CA0D8,
	(u32*) 0x803331D0,
	'W'}
};

void unknownVersion() {
	// can't do much here!
	// we can't output a message on screen without a valid OSFatal addr
	for (;;);
}

// Region detection function
regionData regionDetect() {

	// Default to PAL and 0
	regionData data = {REGION_P, 0};

	// Use instruction to detect region
	switch (*((u32*)0x800CF6CC)) {
		case 0x40820030: data.version = 1; break;
		case 0x40820038: data.version = 2; break;
		case 0x48000465: data.region = REGION_E; data.version = 1; break;
		case 0x2C030000: data.region = REGION_E; data.version = 2; break;
		case 0x480000B4: data.region = REGION_J; data.version = 1; break;
		case 0x4082000C: data.region = REGION_J; data.version = 2; break;
		case 0x38A00001:
			switch (*((u8*)0x8000423A)) {
				case 0xC8: data.region = REGION_K; break;
				case 0xAC: data.region = REGION_W; break;
				default: unknownVersion();
			}
			break;
		default: unknownVersion();
	}

	return data;
}

// Second stage payload loader - loads Kamek binary
int secondStage() {

	// Detect region
	regionData data = regionDetect();

	// Choose functions (these are all the same in v1 and v2, thankfully)
	const loaderFunctionsEx *funcs = &functions[data.region];

	// Load file
	char path[32];
	if (data.version == 0)
		funcs->base.sprintf(path, "/code%c.bin", funcs->identifier);
	else
		funcs->base.sprintf(path, "/code%c%d.bin", funcs->identifier, data.version);
	loadKamekBinaryFromDisc((const loaderFunctions*)funcs, path);

	return 1;
}

// First stage payload loader - removes BCA check, alters GameInitTable and inserts hook to second stage
void firstStage() {

	// Before we can do anything, detect region
	regionData data = regionDetect();
	const loaderFunctionsEx *funcs = &functions[data.region];

	// Patch out the BCA check by nopping the call in the main function
	*funcs->bcaCheck = 0x60000000;
	cacheInvalidateAddress((u32)funcs->bcaCheck);

	// Alter the GameInitTable to load the rels earlier
	// Copy rel loading functions in a buffer
	u32 buffer[3];
	memcpy(&buffer, &funcs->gameInitTable[15], 12);

	// Shift all previous functions by three forwards
	funcs->memmove(&funcs->gameInitTable[3], funcs->gameInitTable, 60);

	// Copy the rel loading functions back in the new spots
	memcpy(funcs->gameInitTable, &buffer, 12);

	// Move all functions after these by one again to make space for the Kamek hook
	funcs->memmove(&funcs->gameInitTable[4], &funcs->gameInitTable[3], 68);

	// Store pointer to the second stage loader in the newly-freed slot
	funcs->gameInitTable[3] = (u32)&secondStage;
	cacheInvalidateAddress((u32)&funcs->gameInitTable[3]);
}

// First stage injection - this is the earliest safe spot we can act at
kmBranch(0x80004320, firstStage);
