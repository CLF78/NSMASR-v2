#include <fBase/dBase/dBaseActor/dActor/dActor.h>
#include <state/sStateID.h>
#include <state/sStateMethod.h>
#include <state/sStateStateMgr.h>

class dActorMultiState_c : public dActor_c {
    public:
        sFStateStateMgr_c<dActorMultiState_c, sStateMethodUsr_FI_c, sStateMethodUsr_FI_c> stateMgr;

        virtual void changeState(const sStateIDIf_c& state);
        virtual void initializeState_GegnericMulti();
        virtual void executeState_GegnericMulti();
        virtual void finalizeState_GegnericMulti();

        static sFStateVirtualID_c<dActorMultiState_c> StateID_GegnericMulti;
};
