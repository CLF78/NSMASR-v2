#include <kamek.h>

// Fix default camera profile bug
// Source: https://github.com/RoadrunnerWMC/NSMBW-Updated/blob/master/code/src/event_controlled_cameras_initialization.cpp
kmCallDefAsm(0x80077290) {
    nofralloc

    li r0, 0
    stb r0, 0x20(r6)
    blr
};

// Disable unnecessary tile allocation, fixes zone size limit
kmWrite32(0x800838C4, 0x480001B0);
