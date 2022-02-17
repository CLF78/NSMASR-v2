#include <kamek.h>
#include <fBase/fBase.h>
#include <fBase/profile.h>
#include <profileid.h>

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
Profile::Profile(buildFunc func, u32 spriteId, const SpriteData* spriteData, u16 executeOrderProfileId, u16 drawOrderProfileId, u32 unk, const char* name, const char** files) {
    u32 profile;

    // Store variables
    this->func = func;
    this->executeOrderProfileId = executeOrderProfileId;
    this->drawOrderProfileId = drawOrderProfileId;
    this->_8 = unk;

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

// ASM Patches to load from the custom lists below

// Spritedata list hooks
kmCallDefAsm(0x80068440) {
    // Check if original sprite (using cr7 because cr0 is in use)
    cmpwi cr7, r0, SPRITECNT*0x28
    blt+ cr7, notCustom

    // Subtract using sub rather than subi because r0
    li r12, SPRITECNT*0x28
    sub r0, r0, r12

    // Override table address
    lis r12, customSprites@h
    ori r12, r12, customSprites@l
    b end

    // Move r30 to r12 to preserve it
    notCustom:
    mr r12, r30

    // Modified original instruction
    end:
    add r28, r12, r0
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

    // Original instruction + skipped instruction
    notCustom:
    lhzx r31, r7, r0
    add r30, r7, r0

    // Return slightly later
    mflr r12
    addi r12, r12, 4
    mtlr r12
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

// Profile list hooks
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

    // Subtract using r12 as r31 needs to be preserved for the next hook
    subi r12, r31, PROFCNT*4

    // Override table address
    lis r7, customProfiles@h
    ori r7, r7, customProfiles@l
    b end

    // Move index to r12 as r31 needs to be preserved for the next hook
    notCustom:
    mr r12, r31

    // Modified original instruction
    end:
    lwzx r0, r7, r12
    blr
}

kmCallDefAsm(0x80162BE4) {
    // Check if original sprite
    cmpwi r31, PROFCNT*4;
    blt+ notCustom

    // Subtract
    subi r31, r31, PROFCNT*4

    // Override table address
    lis r3, customProfiles@h
    ori r3, r3, customProfiles@l

    // Original instruction
    notCustom:
    lwzx r3, r3, r31
    blr
}

// File list hook
kmCallDefAsm(0x8091FD3C) {
    // Check if original sprite
    cmpwi r0, SPRITECNT*4;
    blt+ notCustom

    // Subtract using sub rather than subi because r0
    li r12, SPRITECNT*4
    sub r0, r0, r12

    // Override table address
    lis r12, customSpriteFiles@h
    ori r12, r12, customSpriteFiles@l
    b end

    // Move r25 to r12 to preserve it
    notCustom:
    mr r12, r25

    // Modified original instruction
    end:
    lwzx r21, r12, r0
    blr
}

// Profile names hook
kmBranchDefCpp(0x801018CC, NULL, const char*, u16 profileId, const char** array) {
    if (profileId < ProfileId::OriginalNum)
        return array[profileId];
    return customProfileNames[profileId - ProfileId::OriginalNum];
}
