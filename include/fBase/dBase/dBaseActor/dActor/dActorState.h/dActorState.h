#pragma once
#include <fBase/dBase/dBaseActor/dActor/dActor.h>
#include <state/sStateMethod.h>
#include <state/sStateMgr.h>

class dActorState_c : public dActor_c {
    public:
        sFStateMgr_c<dActorState_c, sStateMethodUsr_FI_c> stateMgr;

        virtual void initializeState_Gegneric();
        virtual void executeState_Gegneric();
        virtual void finalizeState_Gegneric();
};
