#pragma once
#include <fBase/dBase/dBaseActor/dActor/dActor.h>
#include <fBase/dBase/dMessageWindow.h>

class dMessageSpawner_c : public dActor_c {
    public:
        dMessageSpawner_c();

        virtual int create();
        virtual int preCreate();

        virtual int execute();

        dMessageWindow_c* box;
        bool eventTriggered;
        bool activateOnce;

        static dMessageSpawner_c* build();
};
