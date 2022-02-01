#pragma once

#include <kamek.h>

class dQuake_c {
    public:
        struct SpeedStruct {
            float speed;
            float result;
            float multiplier;
            float accel;
            float min;
        };

        SpeedStruct speedVals[2]; // 2nd entry is more relevant
        float screenXOffset;
        float screenYOffset;
        u32 flag; // &1 to call dEn_c::add2ToYSpeed(), &2 to call dEn_c::powBlockActivated(0), &4 to call dEn_c::powBlockActivated(1)
        u32 anotherFlag; // &0x10 is checked but never set apparently??
        bool quakeOn;
        u8 playerId; // If -1, it affects all players
        // 2 bytes padding
        int powLength;
        int mpgpLength;
};
