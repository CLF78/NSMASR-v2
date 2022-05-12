#include <kamek.h>

// Patch BRSTM length automatically (original code by Elias)
kmCallDefAsm(0x80269474) {
    // Let me free
    nofralloc

    // Override value
    lis r31, 0x7FFF
    ori r31, r31, 0xFFFF
    blr
}

// Patch playable BRSTM count
kmWrite32(0x80276A34, 0x38000040);
kmWrite32(0x80276A3C, 0x38000040);
