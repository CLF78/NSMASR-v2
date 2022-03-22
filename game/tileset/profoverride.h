#pragma once

#include <kamek.h>

#define PROFDATA "BG_prof/prof_overrides.bin"
#define PROFSPECVERSION 1

#define PROFILEPAL 0
#define PROFILEKOR 1
#define PROFILECHN 2

struct ProfsBinEntry {
    u8 tileNumber;
    // 1 byte padding
    u16 actorID;
    u8 railColorIndex; // custom field, byte unused by game
    u8 railTexSrtIndex; // custom field, byte unused by game
    // 2 bytes padding
    float xOffs, yOffs, zOffs;
    float xScale, yScale;
    u32 settings;
};

struct ProfsBin {
    u8 version;
    u8 actorIDVersion;
    u8 numEntries;
    u8 numColors;
    u8 numScales;
    // 3 bytes padding
    ProfsBinEntry entries[];
    // 8-bit rgba color table follows
    // vec2 scale table follows
};
