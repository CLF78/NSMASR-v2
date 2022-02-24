#pragma once

#include <kamek.h>

#define PROFDATA "BG_prof/prof_overrides.bin"
#define PROFSPECVERSION 1

#define PROFILEPAL 0
#define PROFILEKOR 1
#define PROFILECHN 2

// Define for common.cpp
#define PROFOVERRIDECPP

struct ProfsBinEntry {
    u8 tileNumber;
    u8 actorIDVersion;
    u16 actorID;
    // 2 bytes padding
    float xOffs, yOffs, zOffs;
    float xScale, yScale;
    u32 settings;
};

struct ProfsBin {
    u8 version;
    u8 railColor;
    // 2 bytes padding
    ProfsBinEntry entries[];
};
