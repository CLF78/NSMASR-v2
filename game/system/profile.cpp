#include <kamek.h>
#include <fBase/fBase.h>
#include <fBase/profile.h>
#include <fBase/profileid.h>

// Arrays of data used by the game
extern SpriteData sprites[SpriteId::OriginalNum];
SpriteData customSprites[SpriteId::Num - SpriteId::OriginalNum];

extern Profile* profiles[ProfileId::OriginalNum];
Profile* customProfiles[ProfileId::Num - ProfileId::OriginalNum];

extern const char** spriteFiles[SpriteId::OriginalNum];
const char** customSpriteFiles[SpriteId::Num - SpriteId::OriginalNum];

extern const char* profileNames[ProfileId::OriginalNum];
const char* customProfileNames[ProfileId::Num - ProfileId::OriginalNum];

// Custom Profile ctor by AboodXD, edited by myself
Profile::Profile(void* buildFunc, u32 spriteId, const SpriteData* spriteData, u16 executeOrderProfileId, u16 drawOrderProfileId, u32 flags, const char* name, const char** files) {
    u32 profile;

    // Store variables
    this->buildFunc = buildFunc;
    this->executeOrderProfileId = executeOrderProfileId;
    this->drawOrderProfileId = drawOrderProfileId;
    this->flags = flags;

    // If spritedata is not null, store this as a sprite
    if (spriteData) {
        profile = spriteData->profileId;
        if (spriteId < SpriteId::OriginalNum) {
            sprites[spriteId] = *spriteData;
            spriteFiles[spriteId] = files;
        } else {
            customSprites[spriteId - SpriteId::OriginalNum] = *spriteData;
            customSpriteFiles[spriteId - SpriteId::OriginalNum] = files;
        }

    // Else use it as a profile id
    } else
        profile = spriteId;

    // Store profile data
    if (profile < ProfileId::OriginalNum) {
        profiles[profile] = this;
        profileNames[profile] = name;
    } else {
        customProfiles[profile - ProfileId::OriginalNum] = this;
        customProfileNames[profile - ProfileId::OriginalNum] = name;
    }
}

/* Spritedata List hooks */

kmCallDefAsm(0x80068440) {
    // Move r30 to r4 to preserve it, as we are inside a loop
    mr r4, r30

    // Check if original sprite (using cr7 because cr0 is in use)
    cmpwi cr7, r0, SPRITECNT*0x28
    blt+ cr7, notCustom

    // Subtract using sub rather than subi because r0
    li r12, SPRITECNT*0x28
    sub r0, r0, r12

    // Override table address
    lis r12, customSprites@h
    ori r12, r12, customSprites@l

    // Modified original instruction
    notCustom:
    add r28, r4, r0
    blr
}

kmCallDefAsm(0x80068E18) {
    // Check if original sprite
    cmpwi r0, SPRITECNT*0x28
    blt+ notCustom

    // Subtract using sub rather than subi because r0
    li r12, SPRITECNT*0x28
    sub r0, r0, r12

    // Override table address
    lis r9, customSprites@h
    ori r9, r9, customSprites@l

    // Original instruction
    notCustom:
    lhzx r0, r9, r0
    blr
}

kmCallDefAsm(0x80068F50) {
    // Check if original sprite
    cmpwi r0, SPRITECNT*0x28;
    blt+ notCustom

    // Subtract using sub rather than subi because r0
    li r12, SPRITECNT*0x28
    sub r0, r0, r12

    // Override table address
    lis r3, customSprites@h
    ori r3, r3, customSprites@l

    // Original instruction
    notCustom:
    lhzx r3, r3, r0
    blr
}

kmCallDefAsm(0x807FC8D8) {
    // Check if original sprite
    cmpwi r0, SPRITECNT*0x28;
    blt+ notCustom

    // Subtract using sub rather than subi because r0
    li r12, SPRITECNT*0x28
    sub r0, r0, r12

    // Override table address
    lis r7, customSprites@h
    ori r7, r7, customSprites@l

    // Original instruction
    notCustom:
    lhzx r31, r7, r0
    blr
}

kmCallDefAsm(0x8006894C) {
    // Check if original sprite (using cr7 because cr0 is in use)
    cmpwi cr7, r4, SPRITECNT*0x28;
    blt+ cr7, notCustom

    // Subtract
    subi r4, r4, SPRITECNT*0x28

    // Override table address
    lis r0, customSprites@h
    ori r0, r0, customSprites@l

    // Original instruction
    notCustom:
    add r31, r0, r4
    blr
}

/* Profile List hooks */

kmCallDefAsm(0x8006C7C8) {
    // Check if original sprite
    cmpwi r0, PROFCNT*4;
    blt+ notCustom

    // Subtract
    li r12, PROFCNT*4
    sub r0, r0, r12

    // Override table address
    lis r4, customProfiles@h
    ori r4, r4, customProfiles@l

    // Original instruction
    notCustom:
    lwzx r4, r4, r0
    blr
}

kmCallDefAsm(0x80161CF4) {
    // Check if original sprite
    cmpwi r0, PROFCNT*4;
    blt+ notCustom

    // Subtract
    li r12, PROFCNT*4
    sub r0, r0, r12

    // Override table address
    lis r3, customProfiles@h
    ori r3, r3, customProfiles@l

    // Original instruction
    notCustom:
    lwzx r3, r3, r0
    blr
}

kmCallDefAsm(0x80162BC8) {
    // Check if original sprite
    cmpwi r31, PROFCNT*4;
    blt+ notCustom

    // Subtract
    subi r31, r31, PROFCNT*4

    // Override table address
    lis r7, customProfiles@h
    ori r7, r7, customProfiles@l

    // Original instruction
    notCustom:
    lwzx r0, r7, r31
    blr
}

// This simply modifies the lwzx instruction to match the previous one, as the registers are untouched from the previous hook
kmWrite8(0x80162BE5, 0x67);

/* File List hook */

kmCallDefAsm(0x8091FD3C) {
    // Move r25 to r21 to preserve it
    mr r21, r25

    // Check if original sprite
    cmpwi r0, SPRITECNT*4;
    blt+ notCustom

    // Subtract using sub rather than subi because r0
    li r12, SPRITECNT*4
    sub r0, r0, r12

    // Override table address
    lis r21, customSpriteFiles@h
    ori r21, r21, customSpriteFiles@l

    // Modified original instruction
    notCustom:
    lwzx r21, r21, r0
    blr
}

/* Profile Names hook */

kmBranchDefCpp(0x801018CC, NULL, const char*, u16 profileId, const char** array) {
    if (profileId < ProfileId::OriginalNum)
        return array[profileId];
    return customProfileNames[profileId - ProfileId::OriginalNum];
}
