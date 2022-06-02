// Source: https://github.com/aboood40091/NewerSMBW/blob/more-sprites/Kamek/src/profile.cpp
// Source: https://github.com/aboood40091/NewerSMBW/blob/more-sprites/Kamek/include/profile.h
#include <kamek.h>

struct SpriteData {
    u16 profileId;
    s32 xoffs;
    s32 yoffs;
    s32 spawnRangeOffset[2];
    s32 spawnRangeSize[2];
    u16 _1C[2];
    u16 _20[2];

    /* Values:
    0x2: always spawn even if offscreen
    0x8: something with z-order
    0x10: grouped sprite */
    u16 flags;
};

class Profile {
    public:
        Profile(void* buildFunc, u32 spriteId, const SpriteData* spriteData, u16 executeOrderProfileId, u16 drawOrderProfileId, u32 flags, const char* name, const char** files=NULL);

        void* buildFunc;
        u16 executeOrderProfileId;
        u16 drawOrderProfileId;

        /* This field is only present in a few profiles, but having it here shouldn't hurt
        Values:
        0x2: always draws the actor
        0x4: supports kill combos??
        0x8: makes Mario look at the actor
        0x10: killed by level clear
        0x20: killed by level clear and awards score
        0x40: only set on balloons??
        0x80: can be killed by iceballs (magic/podobooos/etc)
        0x200: bounces Penguin Mario back when sliding into the actor
        0x400: ignores wrap around edges */
        u32 flags;
};
