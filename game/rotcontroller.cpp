#include <kamek.h>

// Extern for asm calls
extern "C" {
void ApplyRotation(s16 rotation, s16* dest, u32 settings);
void ApplyRotation2(s16 rotation, s16* dest, s16 rotation2, s16* dest2, u32 settings);
}

// This applies to coins and swaying blocks
void ApplyRotation(s16 rotation, s16* dest, u32 settings) {

    // If nybble 7 bit 4 is set, do not set the rotation
    if ((settings >> 20) & 1)
        return;

    // Else set it
    *dest = rotation;
}

// This applies to spinning blocks only, because otherwise they cannot be hit
void ApplyRotation2(s16 rotation, s16* dest, s16 rotation2, s16* dest2, u32 settings) {

    // If nybble 7 bit 4 is set, do not set the rotations
    if ((settings >> 20) & 1)
        return;

    // Else set them
    *dest = rotation;
    *dest2 = rotation2;
}

// Rotation Controlled Coin - Spinning
kmBranchDefAsm(0x809E56D4, 0x809E56D8) {

    // No need for stack saving
    nofralloc

    // Call CPP function
    addi r4, r28, 0x104
    lwz r5, 0x4(r28)
    bl ApplyRotation

    // Restore registers
    lha r0, 0xAF2(r28)
    add r0, r29, r0
    addi r4, r1, 0xE
    blr
}

// Rotation Controlled Coin - Swaying
kmCallDefAsm(0x809E5780) {

    // No need for stack saving
    nofralloc

    // Call CPP function
    mr r3, r29
    addi r4, r28, 0x104
    lwz r5, 0x4(r28)
    b ApplyRotation
}

// Rotation Controlled Block - Spinning
kmBranchDefAsm(0x809C169C, 0x809C16A8) {

    // No need for stack saving
    nofralloc

    // Call CPP function
    addi r4, r29, 0x104
    mr r5, r30
    addi r6, r29, 0x712
    lwz r7, 0x4(r29)
    bl ApplyRotation2

    // Restore registers
    lha r0, 0x726(r29)
    addi r4, r1, 0xE

    // Skipped instruction
    add r0, r30, r0
    blr
}

// Rotation Controlled Block - Swaying
kmCallDefAsm(0x809C176C) {

    // No need for stack saving
    nofralloc

    // Call CPP function
    mr r3, r30
    addi r4, r29, 0x104
    lwz r5, 0x4(r29)
    b ApplyRotation
}

// Rotation Controlled Coin - Fix Double Rotation Bug (by RoadrunnerWMC)
// Source: https://github.com/RoadrunnerWMC/NSMBW-Updated/blob/master/code/src/rotation_controlled_actors_starting_rotation.cpp
kmWrite32(0x809E55F4, 0x3860C000);
kmWrite32(0x809E560C, 0x3860C000);

// Rotation Controlled Block - Fix Double Rotation Bug (by RoadrunnerWMC)
// Source: https://github.com/RoadrunnerWMC/NSMBW-Updated/blob/master/code/src/rotation_controlled_actors_starting_rotation.cpp
kmWrite32(0x809C15C4, 0x3860C000);
kmWrite32(0x809C15DC, 0x3860C000);
