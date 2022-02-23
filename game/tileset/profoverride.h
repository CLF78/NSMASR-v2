#pragma once

#include <kamek.h>

#define OVERRIDEFILE "BG_prof/prof_overrides.bin"
#define SPECVERSION 1

#define PROFILEPAL 0
#define PROFILEKOR 1
#define PROFILECHN 2

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
