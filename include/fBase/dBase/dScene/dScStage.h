#include <kamek.h>
#include <fBase/dBase/dMessageWindow.h>
#include <fBase/dBase/dScene/dScene.h>
#include <s/sPhase.h>
#include <dActorMng.h>
#include <dFader.h>
#include <dQuake.h>
#include <PauseManager.h>

struct ExitMode {
    enum Value {
        BeatLevel,
        LoseLevel,
        ExitLevel,
    };
};

class dScStage_c : public dScene_c {
    public:
        u32 frameCount;
        sPhase_c initChain;
        dQuake_c quake;
        PauseManager_c pauseManager;
        dActorMng_c actorMgr;

        /* NOT IMPLEMENTED YET
        dEnemyMng_c enemyMgr;
        dBeansKuriboMng_c microGoombaMgr;
        dWaterEntryMng_c waterMgr; // done
        dEffActorMng_c effectExplosionMgr; // done
        dTenCoinMng_c redRingMgr;
        dBlockMng_c blockMgr; // done
        dScoreMng_c scoreMgr;
        dCurtainMng_c curtainMgr;
        */
        u8 undefinedstructs[0xE88];

        u8 unk[0x20];

        void* gameDisplay;
        void* goalManager;
        void* smallScoreManager;
        void* fukidashiManager;
        void* courseTimeUp;
        void* miniGameCannon;
        void* miniGameWire;
        void* modelPlayManager;
        dMessageWindow_c* messageWindow;
        void* modelPlayGuide;
        u8* staffCreditScore;
        void* theEnd;
        void* yesNoWindow;

        u8 unk2[4];

        u8 currentWorld;
        u8 currentLevel;
        u8 currentArea;
        u8 currentZone;
        u8 currentLayer;
        u8 currentEntrance;
        // 2 bytes padding

        int ptmfIndex;

        static u32 mCollectionCoin[3]; // Each coin is set to the player id who collected it, else it's 4
        static u32 m_gameMode; // uses the values from ScreenType
        static u32 m_exitMode;

        static dScStage_c* m_instance;

        static void saveLevelProgress(bool isSecretExit, bool isSuperGuide, int world, int level); // Not actually part of the class, but it fits here so :p
        static void returnToScene(u32 profileId, u32 settings, u32 exitMode, dFader_c::fader_type_e fadeType); // Same here

        static void goToTitleScreen(bool isTitleReplay, bool isReset); // unofficial name
};
