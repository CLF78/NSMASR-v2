#include <kamek.h>
#include <dCdFile.h>
#include <dInfo.h>
#include <dMj2dGame.h>
#include <dNext.h>
#include <dSaveMng.h>
#include <fBase/dBase/dScene/dScene.h>
#include <fBase/dBase/dScene/dScRestartCrsin.h>
#include <fBase/dBase/dScene/dScStage.h>
#include <fBase/dBase/dScene/dScWMap.h>
#include <profileid.h>
#include <startinfo.h>

// Externs required by asm calls
extern "C" {
void WarpToStage(dNext_c* data, int fromWorld, int fromLevel);
bool IsCourseClear(void* wmObjActor); // Actually a class function
extern StartGameInfo StartGameInfo; // Copy from dInfo_c
}

void WarpToStage(dNext_c* data, int fromWorld, int fromLevel) {

    // Since these values are used quite a bit, preload them
    int destWorld = data->entranceData.destWorld;
    int destLevel = data->entranceData.destLevel;
    bool discardProgress = (data->entranceData.flags & ~FLAG_DISCARD_LEVEL_PROGRESS);

    // Only warp if destWorld and destLevel aren't zero and we are in story mode
    if (destWorld != 0 && destLevel != 0 && dScStage_c::m_gameMode == NORMAL) {

        // Get save game
        dMj2dGame_c* save = dSaveMng_c::m_instance->getSaveGame((s8)-1);

        // Save Star Coins in any case, let's not be assholes
        for (int i = 0; i < 3; i++) {
            if (dScStage_c::mCollectionCoin[i] < 4)
                save->setCollectCoin(fromWorld, fromLevel, 1 << i);
        }

        // Save level progress if the related flag is unset
        if (!discardProgress)
            dScStage_c::saveLevelProgress(bool(data->entranceData.flags & ~FLAG_WARP_SECRET_EXIT), false, fromWorld, fromLevel);

        // Set exit mode to keep powerups
        dScStage_c::m_exitMode = MODE_BEAT_LEVEL;

        // Set world, level, area, screenType and entrance in the startGameInfo
        // Other fields do not need to be reset as they are already correct
        dScRestartCrsin_c::m_startGameInfo.world1 = destWorld-1;
        dScRestartCrsin_c::m_startGameInfo.world2 = destWorld-1;
        dScRestartCrsin_c::m_startGameInfo.level1 = destLevel-1;
        dScRestartCrsin_c::m_startGameInfo.level2 = destLevel-1;
        dScRestartCrsin_c::m_startGameInfo.screenType = NORMAL;
        dScRestartCrsin_c::m_startGameInfo.area = data->entranceData.destArea;
        dScRestartCrsin_c::m_startGameInfo.entrance = data->entranceData.destId;

        // Set previous world in order not to reset the map position
        dScWMap_c::m_PrevWorldNo = 0xFF;

        // Set map node
        dInfo_c::m_instance->exitMapNode = data->entranceData.destMapNode;

        // Set next scene
        dScene_c::setNextScene(ProfileId::RESTART_CRSIN, 0, false);

    // Apparently the exit level option was kind of rushed so it doesn't work correctly in other modes, gotta fix it!
    } else {
        ExitMode keepPowerUps;

        // If we are in extra modes and progress is not to be saved, trigger the game over screen
        // Else if we are in regular gameplay, keep powerup state for consistency
        // Else restore it
        if (dInfo_c::mGameFlag & ~FLAG_EXTRA_MODES && discardProgress) {
            dInfo_c::mGameFlag |= FLAG_GAME_OVER;
            keepPowerUps = MODE_EXIT_LEVEL;
        } else if (dScStage_c::m_gameMode == NORMAL)
            keepPowerUps = MODE_BEAT_LEVEL;
        else
            keepPowerUps = MODE_EXIT_LEVEL;

        // Return to the correct scene (the function manages all the rest on its own)
        dScStage_c::returnToScene(ProfileId::WORLD_MAP, 0, keepPowerUps, data->fade);
    }
}

kmBranchDefAsm(0x800D0250, 0x800D0340) {
    // No stack saving necessary here
    nofralloc

    // Call cpp function
    mr r3, r31
    mr r4, r30
    lbz r5, 0x120D(r28)
    bl WarpToStage

    // Will be replaced by a branch
    blr
}

kmCallDefAsm(0x808CE35C) {
    // Push stack
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)

    // Original instruction
    mr r3, r30

    // Call IsCourseClear
    bl IsCourseClear

    // Reload LR save using r12
    lwz r12, 0x14(r1)

    // If course is cleared, skip check
    cmpwi r3, 1
    beq skipCheck

    // Check if this node is the one we're currently on
    lis r3, StartGameInfo@h
    ori r3, r3, StartGameInfo@l
    lbz r3, 0xD(r3)
    cmpw r3, r5
    bne+ end

    // Otherwise skip open check
    skipCheck:
    addi r12, r12, 0x58

    // Original instruction, pop stack and return
    end:
    mr r3, r30
    mtlr r12
    addi r1, r1, 0x10
    blr
}
