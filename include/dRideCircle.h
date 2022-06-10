#include <kamek.h>
#include <dRide_ctr.h>

class dRideCircle_c : public dRide_ctr_c {
    public:
        VEC2 centreOffset;
        VEC2 leftOffset;
        VEC2 topMaybe;
        float radius;

        s32 rightAngleOffset;
        s32 leftAngleOffset;
        s16 prevRotation;

        bool _72; // ??
        bool _73; // ??
};
