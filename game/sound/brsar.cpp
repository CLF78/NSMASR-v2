#include <kamek.h>
#include <nw4r/snd/BasicSound.h>
#include <nw4r/snd/SoundArchive.h>
#include <nw4r/snd/SoundArchivePlayer.h>
#include <nw4r/snd/SoundHandle.h>
#include <nw4r/snd/SoundStartable.h>
#include <nw4r/ut/FileStream.h>
#include <rvl/dvd/dvd.h>
#include <sound/SndList.h>
#include <stdlib/stdio.h>
#include "sound/brsar.h"

// Extern for ASM calls
extern "C" {
    nw4r::ut::FileStream* MyOpenFileStream(nw4r::snd::SoundArchive* self, ulong fileId, void* buffer, int size, ulong soundId);
    const char* GetCustomPath(const char* originalPath, ulong soundId);
    void SetMusicVolume(float* out, u8 volume);
}

// Temporary id storage
static ulong currentSoundId = STRM_BGM_DUMMY;

// Array of new sounds
const CustomSoundEntry customEntries[] = {
    {SMB_GRASS, "stream/SMB_GRASS.brstm", STRM_BGM_CHIJOU},
    {SMB_GRASS_F, "stream/SMB_GRASS_F.brstm", STRM_BGM_CHIJOU},
};

nw4r::snd::SoundStartable::StartResult mySetupSoundImpl(nw4r::snd::SoundArchivePlayer* self, nw4r::snd::SoundHandle* handle, ulong soundId, nw4r::snd::detail::BasicSound::AmbientInfo* ambientArgInfo, nw4r::snd::SoundActor* actor, bool holdFlag, const nw4r::snd::SoundStartable::StartInfo* startInfo) {

    // Store soundId in the static variable
    currentSoundId = soundId;

    // Skip actual BRSTMs and control tracks
    if ((soundId < STRM_BGM_CHIKA_FAST || soundId > SEQ_BGM_TORIDE_FAST_V) && soundId != STRM_BGM_DUMMY) {

        // Find the corresponding filename
        for (int i = 0; i < sizeof(customEntries) / sizeof(CustomSoundEntry); i++) {
            if (customEntries[i].id == soundId) {

                // Print the filename
                char path[256];
                snprintf(path, sizeof(path), "/Sound/%s", customEntries[i].fileName);

                // Check if file exists, and if so override the soundId
                if (DVDConvertPathToEntrynum(path) != -1)
                    soundId = STRM_BGM_DUMMY;

                // Exit the loop anyway
                break;
            }
        }
    }

    // Call original function
    return self->detail_SetupSoundImpl(handle, soundId, ambientArgInfo, actor, holdFlag, startInfo);
}

nw4r::ut::FileStream* MyOpenFileStream(nw4r::snd::SoundArchive* self, ulong fileId, void* buffer, int size, ulong soundId) {

    // If soundId has been replaced, override the fileId with zero
    if (soundId != currentSoundId)
        fileId = 0;

    // Call original function
    return self->detail_OpenFileStream(fileId, buffer, size);
}

const char* GetCustomPath(const char* originalPath, ulong soundId) {

    // Check if soundId has been replaced
    if (soundId != currentSoundId) {

        // Get the corresponding path
        for (int i = 0; i < sizeof(customEntries) / sizeof(CustomSoundEntry); i++) {
            if (customEntries[i].id == currentSoundId)
                return customEntries[i].fileName;
        }
    }

    // Else fallback to the original
    return originalPath;
}

void SetMusicVolume(float* out, u8 volume) {

    // If the volume is valid, convert it, divide it and store it
    if (volume & 0x7F)
        *out = (float)volume / 127.0f;
}

// Patch BRSTM length automatically (original code by Elias)
kmCallDefAsm(0x80269474) {

    // Let me free
    nofralloc

    // Override value
    lis r31, 0x7FFF
    ori r31, r31, 0xFFFF
    blr
}

// Patch playable BRSTM count
kmWrite32(0x80276A34, 0x38000040);
kmWrite32(0x80276A3C, 0x38000040);

// Replace calls to SetupSoundImpl to inject the soundId
kmBranch(0x802756E8, mySetupSoundImpl);
kmBranch(0x80275708, mySetupSoundImpl);
kmBranch(0x80278C00, mySetupSoundImpl);

// Replace call to ReadSoundInfo to read the original info
kmCallDefCpp(0x80278C8C, bool, nw4r::snd::SoundArchive* self, ulong soundId, nw4r::snd::SoundArchive::SoundInfo* soundInfo) {

    // Check if the soundId has been replaced
    if (soundId != currentSoundId) {

        // Get the base soundId if so
        for (int i = 0; i < sizeof(customEntries) / sizeof(CustomSoundEntry); i++) {
            if (customEntries[i].id == currentSoundId) {
                soundId = customEntries[i].baseSoundId;
                break;
            }
        }
    }

    // Call original function
    return self->ReadSoundInfo(soundId, soundInfo);
}

// Replace call to OpenFileStream to read the original fileId
kmCallDefAsm(0x80279AC8) {

    // No stack saving necessary
    nofralloc

    // Call CPP function
    mr r7, r20
    b MyOpenFileStream
}

// Replace call to SetId to set the original soundId
kmCallDefCpp(0x8027915C, void, nw4r::snd::detail::BasicSound* self, ulong originalSoundId) {
    self->SetId(currentSoundId);
}

// Replace external file path
kmBranchDefAsm(0x802759F0, 0x802759F4) {

    // No stack saving needed
    nofralloc

    // Call CPP function
    mr r3, r26
    mr r4, r20
    bl GetCustomPath

    // Move resulting path to r26 and return
    mr r26, r3
    blr
}

// BRSTM volume override (by MrBean35000vr, edited by Melg)
kmBranchDefAsm(0x8027C430, 0x8027C434) {

    // No stack saving needed
    nofralloc

    // Call CPP function
    lwz r3, 0x74(r1)
    subi r3, r3, 0x5C
    lbz r4, 0x3F(r29)
    bl SetMusicVolume

    // Original instruction
    lwz r3, 0(r30)
    blr
}
