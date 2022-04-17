#pragma once
#include <kamek.h>
#include <startinfo.h>

struct GameFlag {
    enum Value {
        DisableActorSpawning = 1,
        IsStopped = 2, // enables player state change freeze
        LevelLoadedMaybe = 4,
        ExtraMode = 0x10,
        GameOver = 0x20,
        CoinBattle = 0x40,
    };
};

class dInfo_c {
    public:
        u8 unk[0x3C];
        u32 currWorld;
        u32 currLevel;
        u32 exitMapNode;

        static StartGameInfo m_startGameInfo;
        static u32 mGameFlag;
        static dInfo_c* m_instance;
};
