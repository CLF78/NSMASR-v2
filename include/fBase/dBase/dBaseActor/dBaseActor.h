#pragma once
#include <kamek.h>
#include <c/cList.h>
#include <fBase/dBase/dBase.h>

class dBaseActor_c : public dBase_c {
    public:
        enum ActorType {
            MapActor = 0,
            MapDemoActor = 1,
            MapEnemy = 2,
            Generic = 8,
        };

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

        dBaseActor_c();

        virtual int preCreate();
        virtual void postCreate(fBase_c::MAIN_STATE_e status);

        virtual int preDelete();
        virtual void postDelete(fBase_c::MAIN_STATE_e status);

        virtual int preExecute();
        virtual void postExecute(fBase_c::MAIN_STATE_e status);

        virtual int preDraw();
        virtual void postDraw(fBase_c::MAIN_STATE_e status);

        virtual ~dBaseActor_c();

        virtual void draw2D();
        virtual void draw2DSpecial();

        virtual int GetActorType();

        virtual void finalUpdate();
};
