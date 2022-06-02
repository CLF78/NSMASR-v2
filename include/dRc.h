#include <kamek.h>

// Forward declaration
class dActor_c;
class dBc_c;
class dRide_ctr_c;

class dRc_c {
    public:
        void* vtable;

        dActor_c* owner;
        VEC3* ownerPos;

        dRc_c* next;

        dRide_ctr_c* ride[2];
        dBc_c* bc;

        float _1C;
        float _20;
        float _24;
        float _28;

        s16 rotation;
        u8 chainlinkMode;
        u8 rideType; // 0 = dRideRoll_c, 2 = dRide2Point_c, 4 = dRideCircle_c
        u8 flags; // &1 = ??, &2 = ??, &4 = set on player when riding Lakitu Clouds/Clown Cars
        u8 _31; // bool maybe?
        u8 layer;
        // 1 byte padding
};
