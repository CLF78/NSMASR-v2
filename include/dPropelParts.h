#pragma once

#include <kamek.h>
#include <m/mEf/levelEffect.h>

class dActor_c;

class dPropelParts_c {
    public:
        void* vtable;
        dActor_c* parent;
        u32 status; // 3 = isLiftUp, other values unknown
        s16 angle; // unsure
        // 2 bytes padding
        float rotSpeed; // unsure
        mEf::levelEffect_c effect;
        float effectScale;
};
