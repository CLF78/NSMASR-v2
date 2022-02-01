#pragma once

#include <kamek.h>
#include <dMj2dHeader.h>
#include <dMj2dGame.h>

class dSaveMng_c {
    public:
        u32 _0[8];
        dMj2dHeader_c save;

        static dSaveMng_c* m_instance;

        dMj2dGame_c* getSaveGame(s8 slot);
};
