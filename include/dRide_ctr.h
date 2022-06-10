#include <kamek.h>
#include <dRc.h>

class dActor_c;

class dRide_ctr_c {
    public:
        void* vtable;
        dActor_c* owner;

        dRide_ctr_c* prev;
        dRide_ctr_c* next;

        dRc_c* linkedRc;

        VEC2 right;
        VEC2 left;
        VEC2 length;
        VEC2 lastLeft;

        float lineLength;
        float leftYDelta;

        u32 flags;
        s16 rotation;
        u8 type; // 0 = dRideRoll_c, 2 = dRide2Point_c, 4 = dRideCircle_c

        bool _43;
        bool linked;

        u8 chainlinkMode;
        bool _46;
        u8 subType;
        u8 _48; // unused?
        u8 _49; // unused?
        u8 layer;
        u8 _4B; // unused?

        static dRide_ctr_c* mEntryN;
        static dRide_ctr_c* mEntryB;
};
