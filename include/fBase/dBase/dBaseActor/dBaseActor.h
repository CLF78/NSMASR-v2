#pragma once

#include <kamek.h>
#include <c/cList.h>
#include <fBase/dBase/dBase.h>
#include <rvl/mtx/mtx.h>

class dBaseActor_c : dBase_c {
    public:
        cListNd_c linkActor;
        MTX34 matrix;

        VEC3 pos;
        VEC3 lastPos;
        VEC3 posDelta;

        VEC3 centerOffs;
        VEC3 scale;
        VEC3 speed;
        VEC3 speedMax;

        S16VEC angle;
        S16VEC moveAngle;

        float speedF;
        float accelF;
        float accelY;
        float accelFall;
        float accelX;

        u32 lookAtSettings; // copied from Profile
        bool visible;
        u8 _125; // set to 0 in dActor_c and never used again
        // 2 bytes padding
};
