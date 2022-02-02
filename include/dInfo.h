#pragma once

#include <kamek.h>
#include <startinfo.h>

class dInfo_c {
    public:
        u8 unk[0x44];
        u32 exitMapNode;

        static StartLevelInfo m_startGameInfo;
        static dInfo_c* m_instance;
};
