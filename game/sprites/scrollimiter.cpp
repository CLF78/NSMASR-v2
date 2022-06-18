#include <kamek.h>

// Reset zone borders to fix horizontal scroll limiters
kmCallDefAsm(0x8015620C) {
    nofralloc

    // Copy the zone borders over
    stfs f23, 0x30(r3)
    stfs f23, 0x40(r3)
    stfs f23, 0x50(r3)
    stfs f22, 0x34(r3)
    stfs f22, 0x44(r3)
    stfs f22, 0x54(r3)

    // Original instruction
    li r22, 0
    blr
}
