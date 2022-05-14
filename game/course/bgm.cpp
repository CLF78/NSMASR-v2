#include <kamek.h>
#include <sound/SndList.h>
#include <sound/SndSceneMgr.h>

// Index begins from musicId 28
// First value is the regular BRSTM stream, second one is the fast BRSTM stream
const u32 CustomMusicIds[1][2] = {
    {SE_MAX, SE_MAX+1}, // dummy entry to showcase how this works
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
