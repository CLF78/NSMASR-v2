#pragma once
#include <kamek.h>
#include <fBase/dBase/dBaseActor/dBaseActor.h>
#include <fBase/profile.h>
#include <fBase/profileid.h>

class dEffectSpawner_c : public dBaseActor_c {
    public:
        virtual int create();
        virtual int execute();

        u64 eventFlag;
        float scale;
        u16 effect;
        u16 timer;
        u16 delay;
        bool isGFX;
        bool runOnce;

        static dEffectSpawner_c* build();
};

// TODO: profile
