#include <kamek.h>

// Fix unnecessary physics reinitialization
kmWrite32(0x80A09C90, 0x48000010);
kmWrite32(0x80A09CD4, 0x48000048);

// Disable invisible wall option
kmCallDefAsm(0x80A09B80) {

    // No stack saving needed
    nofralloc

    // Original instruction
    stb r0, 0x970(r31)

    // Get settings
    lwz r0, 0x4(r31)

    // Get LR
    mflr r12

    // Get nybble 6 bit 4 (multiplied by 4)
    rlwinm r0, r0, 10, 29, 29

    // Add it to the LR and return
    add r12, r12, r0
    mtlr r12
    blr
}

// Custom style option
kmCallDefAsm(0x80A0A0AC) {

    // Mo stack saving needed
    nofralloc

    // Get settings
    lwz r4, 0x4(r3)

    // Get nybble 7 multiplied by 4
    rlwinm r4, r4, 14, 26, 29

    // Add it to the index
    add r5, r5, r4

    // Original instruction
    xoris r5, r5, 0x8000
    blr
}

// A fix because BrawlBox/Crate corrupt VIS0 animations
kmCallDefAsm(0x80A0A2EC) {

    // Original instruction
    fmr f1, f31

    // Load 0.25 using an unused part of the stack
    lis r3, 0x3E80
    stw r3, 0x20(r1)
    lfs f2, 0x20(r1)

    // Multiply
    fmuls f1, f1, f2
    blr
}
