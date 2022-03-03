#pragma once

#include <kamek.h>
#include <startinfo.h>

enum GameFlag {
    FLAG_DISABLE_ACTOR_SPAWNING = 0x1,
    FLAG_IS_STOPPED = 0x2, // enables player state change freeze
    FLAG_LEVEL_LOADED_MAYBE = 0x4,
    FLAG_EXTRA_MODES = 0x10,
    FLAG_GAME_OVER = 0x20,
    FLAG_COIN_BATTLE = 0x40,
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
