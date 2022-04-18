#pragma once
#include <kamek.h>
#include <m/mTypes.h>

class dEffActorMng_c {
    public:
        u16 count; // Only incremented/decremented once per shard set

        bool createBlockFragEff(mVec3_c& position, ulong settings, s8 playerId);

        static dEffActorMng_c* m_instance;
};
