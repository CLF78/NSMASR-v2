#include <kamek.h>
#include <dSwitchFlagMng.h>

// NOTE: The following code assumes the actor spawner uses sprite id 484,
// since C++ syntax cannot be used in assembly snippets. Change it if you need to.

// Extern for ASM calls
extern "C" {
bool CheckEvent(u8 event);
}

bool CheckEvent(u8 event) {
    return (dSwitchFlagMng_c::m_instance->flags & (u64)(1 << event));
}

// ID Replacement Subroutine
static asm void ActorSpawnerIDReplace() {

    // No stack saving needed
    nofralloc

    // Original instruction
    lhz r0, 0(r4)

    // Check for the actor spawner sprite id
    cmpwi r0, 484
    bnelr+

    // If so replace with the actual sprite
    lhz r0, 0xE(r4)
    rlwinm r0, r0, 0, 22, 31
    blr
}

// Force Sprite Creation
kmWrite32(0x800686DC, 0x60000000);

// ID Replacement #1
kmCallDefAsm(0x80068430) {

    // No stack saving needed
    nofralloc

    // Original instruction
    lhz r0, 0(r16)

    // Check for the actor spawner sprite id
    cmpwi r0, 484
    bnelr+

    // If so replace with the actual sprite
    lhz r0, 0xE(r16)
    rlwinm r0, r0, 0, 22, 31
    blr
}

// ID Replacement #2
kmCallDefAsm(0x80068930) {

    // No stack saving needed
    nofralloc

    // Original instruction
    lhz r0, 0(r30)

    // Check for the actor spawner sprite id
    cmpwi r0, 484
    bnelr+

    // If so replace with the actual sprite
    lhz r0, 0xE(r30)
    rlwinm r0, r0, 0, 22, 31
    blr
}

// ID Replacement # 3
kmCall(0x80068DF4, ActorSpawnerIDReplace);

// ID Replacement #4
kmCallDefAsm(0x80068F30) {

    // No stack saving needed
    nofralloc

    // Original instruction
    lhz r0, 0(r27)

    // Check for the actor spawner sprite id
    cmpwi r0, 484
    bnelr+

    // If so replace with the actual sprite
    lhz r0, 0xE(r27)
    rlwinm r0, r0, 0, 22, 31
    blr
}

// ID Replacement #5
kmCallDefAsm(0x8091FD34) {

    // No stack saving needed
    nofralloc

    // Original instruction
    lhz r0, 0(r24)

    // Check for the actor spawner sprite id
    cmpwi r0, 484
    bnelr+

    // If so replace with the actual sprite
    lhz r0, 0xE(r24)
    rlwinm r0, r0, 0, 22, 31
    blr
}

// ID Replacement #6
kmCall(0x807FC8B4, ActorSpawnerIDReplace);

// Event Check #1
kmBranchDefAsm(0x800685CC, 0x800685D0) {

    // No stack saving needed
    nofralloc

    // Get original sprite id again
    lhz r3, 0(r16)

    // If it's not the actor spawner, keep going
    cmpwi r3, 484
    bne+ end

    // Check the events using a dedicated function
    lhz r3, 0xE(r16)
    rlwinm r3, r3, 22, 26, 31
    bl CheckEvent

    // Move result to r20
    mr r20, r3

    // Original instruction
    end:
    cmpwi r20, 0
    blr
}

// Event Check #2
kmBranchDefAsm(0x80068B3C, 0x80068B40) {

    // No stack saving needed
    nofralloc

    // Get original sprite id again
    lhz r3, 0(r30)

    // If it's not the actor spawner, keep going
    cmpwi r3, 484
    bne+ end

    // Check the events using a dedicated function
    lhz r3, 0xE(r30)
    rlwinm r3, r3, 22, 26, 31
    bl CheckEvent

    // Move result to r28
    mr r28, r3

    // Original instruction
    end:
    cmpwi r28, 0
    blr
}
