#pragma once

#include <kamek.h>
#include <dActorMng.h>
#include <dFader.h>
#include <dQuake.h>
#include <PauseManager.h>
#include <s/sPhase.h>

typedef enum {
    MODE_BEAT_LEVEL,
    MODE_LOSE_LEVEL,
    MODE_EXIT_LEVEL,
} ExitMode;

class dScStage_c : dScene_c {
    public:
        u32 frameCount;
        sPhase_c initChain;
        dQuake_c quake;
        PauseManager_c pauseManager;
        dActorMng_c actorMgr;

        /* NOT IMPLEMENTED YET
        dEnemyMng_c enemyMgr;
        dBeansKuriboMng_c microGoombaMgr;
        dWaterEntryMng_c waterMgr;
        dEffActorMng_c effectExplosionMgr;
        dTenCoinMng_c redRingMgr;
        dBlockMng_c blockMgr;
        dScoreMng_c scoreMgr;
        dCurtainMng_c curtainMgr;

        u8 unk[0x20];

        void *gameDisplay;
        void *goalManager;
        void *smallScoreManager;
        void *fukidashiManager;
        void *courseTimeUp;
        void *miniGameCannon;
        void *miniGameWire;
        void *modelPlayManager;
        void *messageWindow;
        void *modelPlayGuide;
        u8 *staffCreditScore;
        void *theEnd;
        void *yesNoWindow;

        u8 unk2[4];

        u8 CurrentWorld;
        u8 CurrentLevel;
        u8 CurrentArea;
        u8 CurrentZone:
        u8 CurrentLayer;
        u8 CurrentEntrance;
        // 2 bytes padding

        int ptmfIndex;
        */

        static u32 mCollectionCoin[3]; // Each coin is set to the player id who collected it, else it's 4
        static u32 m_gameMode; // uses the values from screenType in startinfo.h
        static ExitMode m_exitMode;

        static dScStage_c* m_instance;

        static void saveLevelProgress(bool isSecretExit, bool isSuperGuide, int world, int level); // Not actually part of the class, but it fits here so :p
        static void returnToScene(u32 profileId, u32 settings, ExitMode exitMode, dFader_c::fader_type_e fadeType); // Same here
};
