#pragma once

#include <kamek.h>
#include <startinfo.h>

class dInfo_c {
    public:
        u8 unk[0x44];
        u32 exitMapNode;

        enum GameFlag {
            FLAG_ALWAYS_ON = 0x2,
            FLAG_LEVEL_LOADED_MAYBE = 0x4,
            FLAG_EXTRA_MODES = 0x10,
            FLAG_GAME_OVER = 0x20,
            FLAG_COIN_BATTLE = 0x40,
        };

        static StartGameInfo m_startGameInfo;
        static u32 mGameFlag;
        static dInfo_c* m_instance;
};
