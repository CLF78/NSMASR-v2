#pragma once
#include <kamek.h>

class SndBgmMgr {
    public:
        u32 getCurrentBgm(u32 bgmId); // unofficial name

        static SndBgmMgr* sInstance;
};
