#include <kamek.h>

// Fix connected pipe exit direction
kmCallDefAsm(0x80050A5C) {

    // No stack saving needed
    nofralloc

    // Do the thing
    lbz r3, 0x13(r3)
    addi r0, r3, 3
    blr
}

// Fix incorrect connected pipe state switch
kmCallDefAsm(0x80050A8C) {

    // No stack saving needed
    nofralloc

    // Do the thing
    addi r4, r4, 0x40

    // Original instruction
    li r5, 1
    blr
}

// Fix pipe path node calculation
kmBranchDefAsm(0x800508FC, 0x80050934) {

    // No stack saving needed
    nofralloc

    // Check if connected pipe exit
    rlwinm. r0, r0, 0, 31, 31
    beq notExit

    // If so subtract 2 from node count
    lhz r7, 0x4(r3)
    subi r4, r7, 2
    b originalCode

    // Else set next node to 1
    notExit:
    li r4, 1

    // Original code, moved later so it works
    originalCode:
    sth r4, 0x42C(r31)
    lhz r5, 0x2(r3)
    lwz r6, 0x3C(r6)
    add r0, r5, r4
    slwi r0, r0, 4
    add r5, r6, r0
    blr
}
