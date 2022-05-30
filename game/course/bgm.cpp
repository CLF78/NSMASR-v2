#include <kamek.h>
#include <nw4r/snd/SoundArchive.h>
#include <sound/SndList.h>
#include <sound/SndSceneMgr.h>

// Index begins from musicId 28
// First value is the regular BRSTM stream, second one is the fast BRSTM stream
const u32 CustomMusicIds[][2] = {
    {SMB_GRASS, SMB_GRASS_F},
};

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
