#include <kamek.h>
#include <course/BgData.h>
#include <fBase/dBase/dBaseActor/dActor/daFarBG.h>

extern "C" {
u32 GetFixedBGEnabled(daFarBG_c* farbg);
u32 GetFixedBG(daFarBG_c* farbg);
void SetBGScale(float x, float y, daFarBG_c* farbg);
}

float BGZoomValues[16] = {1.0, 1.25, 1.5, 2.0, 0.1, 0.15, 0.25, 0.375, 0.5, 0.625, 0.75, 0.9, 1.125, 1.75, 2.25, 2.5};

u32 GetFixedBG(daFarBG_c* farbg) {

    // Get background data
    BgData* bgData = farbg->GetMyBgDataP();

    // If the fixed bg id isn't zero use it, else return the hardcoded value
    return (bgData->fixedBgFileId) ? bgData->fixedBgFileId : 0x104;
}

u32 GetFixedBGEnabled(daFarBG_c* farbg) {

    // Get background data
    BgData* bgData = farbg->GetMyBgDataP();

    // If the fixed bg id is zero return 3, else 1
    return (bgData->fixedBgFileId == 0) * 2 + 1;
}

void SetBGScale(float x, float y, daFarBG_c* farbg) {

    // Get background data
    BgData* bgData = farbg->GetMyBgDataP();

    // Get zoom
    u16 zoom = bgData->scale;
    if (zoom >= sizeof(BGZoomValues) / sizeof(float))
        zoom = 0;

    // Get relevant float
    float multiplier = BGZoomValues[zoom];

    // Apply it
    farbg->scale.x = x * multiplier;
    farbg->scale.y = y * multiplier;
}

// Disable original check, remove if you want to keep it!
kmWrite32(0x801180A0, 0x38600001);

// Check if enabled
kmBranchDefAsm(0x801180AC, 0x801180B0) {
    // No stack saving needed
    nofralloc

    // Call CPP function
    mr r3, r24
    bl GetFixedBGEnabled

    // Move result to r0 and return
    mr r0, r3
    blr
}

// Apply modified value
kmBranchDefAsm(0x8011810C, 0x80118110) {
    // No stack saving needed
    nofralloc

    // Call CPP function
    mr r3, r24
    bl GetFixedBG

    // Move result to r4
    mr r4, r3

    // Restore registers and return
    mr r3, r24
    li r0, 0
    blr
}

// Apply scale value
kmBranchDefAsm(0x8011854C, 0x8011857C) {

    // No stack saving needed
    nofralloc

    // Call CPP function
    lfs f1, 0x48C(r31)
    lfs f2, 0x490(r31)
    mr r3, r31
    bl SetBGScale

    blr
}
