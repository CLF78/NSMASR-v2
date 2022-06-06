#include <kamek.h>
#include <sound/SndList.h>

// Add custom sounds to sprite 465
kmCallDefAsm(0x808AC564) {

    // Original instruction
    li r5, 0

    // If type is 0, return
    cmpwi r0, 1
    beqlr+

    // Else set our custom sfx
    li r4, SE_AMB_WATERFALL
    blr
}
