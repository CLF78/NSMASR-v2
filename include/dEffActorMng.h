#pragma once
#include <kamek.h>

class dEffActorMng_c {
    public:
        u16 count; // Only incremented/decremented once per shard set

        static dEffActorMng_c* m_instance;
};
