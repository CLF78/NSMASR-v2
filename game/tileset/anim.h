#pragma once

#include <kamek.h>

#define ANIMDATA "BG_anim/anims.bin"
#define ANIMTILE "BG_anim/anim_%02x.bin"
#define ANIMSPECVERSION 1

struct AnimsBinEntry {
    u16 delayOffs;  // pointer to null-terminated u8 array; offset is relative to start of file
    u8 tileNum;
    bool reverse;
};

struct AnimsBin {
    u8 version;
    u8 numEntries;
    AnimsBinEntry entries[];
    // (the delay arrays are after the entries)
};
