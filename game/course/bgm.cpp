#include <kamek.h>
#include <course/dCd.h>
#include <course/dCdFile.h>
#include <fBase/dBase/dScene/dScStage.h>
#include <nw4r/snd/SoundArchive.h>
#include <sound/SndList.h>
#include <sound/SndBgmMgr.h>
#include <sound/SndSceneMgr.h>

// Extern for asm call
extern "C" {
u32 GetZoneMusic();
}

// Index begins from musicId 28
// First value is the regular BRSTM stream, second one is the fast BRSTM stream
const u32 CustomMusicIds[][2] = {
    {SMB_GRASS, SMB_GRASS_F},
};

u32 GetZoneMusic() {
    return SndBgmMgr::sInstance->getCurrentBgm(dCd_c::getFileP(dScStage_c::m_instance->currentArea)->getAreaBgm(dScStage_c::m_instance->currentZone));
}

// Skip validity check
kmWrite16(0x8019BA68, 0x4800);

// Load additional BRSTMs
kmBranchDefCpp(0x8019E128, NULL, u32, void* unused, u32 musicId) {

    // Add our own validity check
    if (musicId - 0x1C > sizeof(CustomMusicIds) / 8)
        return 0;

    // Return the correct track
    return CustomMusicIds[musicId - 0x1C][SndSceneMgr::sInstance->isFastMusic];
}

// Fix Pausing
kmBranchDefAsm(0x8019D32C, 0x8019D338) {

    // Save stack manually
    nofralloc
    stwu r1, -0x10(r1)
    stw r4, 0xC(r1)

    // Call CPP function
    bl GetZoneMusic

    // Move result, pop stack and return
    mr r31, r3
    lwz r4, 0xC(r1)
    addi r1, r1, 0x10
    blr
}

// Redirect BRSAR SoundType Read
kmCallDefCpp(0x8019E34C, nw4r::snd::SoundArchive::SoundType, nw4r::snd::SoundArchive* self, ulong soundId) {

    if (soundId < STRM_BGM_CHIKA_FAST || soundId > STRM_BGM_HIKOUSEN_ROUKA_FAST)
        soundId = STRM_BGM_CHIJOU;

    return self->GetSoundType(soundId);
}

// Redirect BRSAR SoundUserParam Read
kmCallDefCpp(0x8019E388, ulong, nw4r::snd::SoundArchive* self, ulong soundId) {

    if (soundId < STRM_BGM_CHIKA_FAST || soundId > STRM_BGM_HIKOUSEN_ROUKA_FAST)
        soundId = STRM_BGM_CHIJOU;

    return self->GetSoundUserParam(soundId);
}

// Disable Bahps
kmWrite32(0x8019E204, 0x38600000);
