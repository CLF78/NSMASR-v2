#include <kamek.h>

extern double MagicNumber;

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

// A fix because both BrawlBox/Crate and WSZST corrupt VIS0 animations
kmCallDefAsm(0x80A0A2EC) {

    // Reload settings from the stack
    lwz r3, 0x64(r1)

    // Divide by 4 and keep MSB set
    rlwinm r3, r3, 0, 30, 0

    // Convert to float
    stw r3, 0x64(r1)
    lfd f1, 0x60(r1)
    lis r3, MagicNumber@ha
    lfd f2, MagicNumber@l(r3)
    fsubs f1, f1, f2
    blr
}
