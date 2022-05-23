#pragma once
#include <fBase/dBase/dBaseActor/dActor/dActor.h>
#include <fBase/dBase/dBaseActor/dActor/dActorMultiState/dEn/daEnKuriboBase/daEnKuriboBase.h>
#include <m/m3d/anmtexpat.h>
#include <state/sStateID.h>
#include <dBc.h>
#include <dCc.h>

class daEnKuribo_c : public daEnKuriboBase_c {
    public:
        // Only used for the tumble animation
        pointSensor_s tumbleSensor;

        // These are used in the Auto_Walk state (aka Pipe Generator)
        float targetXPos;
        float targetYPos;

        // This is used in the Down state
        u8 tumbleState; // 0 = initial state, 1 = tumble begin, 2 = tumbling, 3 = tumble end

        // This is used in the Born_Split2 state
        bool moveUpwards; // gets set back to zero once the maximum jump height has been reached

        u16 nybble11;
        m3d::anmTexPat_c* customAnmTexPat; // custom field, originally unused

        // fBase overrides
        virtual int doDelete();
        virtual ~daEnKuribo_c();

        // dBaseActor overrides
        virtual void finalUpdate();

        // dEn overrides
        virtual bool hitCallback_HipAttk(dCc_c* self, dCc_c* other);

        virtual void playEnemyDownSound2(); // unofficial name

        virtual bool createIceActor(); // unofficial name

        virtual void beginFunsui();
        virtual void endFunsui();
        virtual bool isFunsui() const;

        // daEnKuriboBase overrides
        virtual void reactSpinFumiProc(dActor_c* killingActor); // unofficial name
        virtual void reactYoshiFumiProc(dActor_c* killingActor); // unofficial name

        virtual void loadWingModel(); // unofficial name
        virtual void drawModel();

        virtual void initialize();
        virtual void setTurnState(); // unofficial name

        virtual void updateModel(); // unofficial name
        virtual void walkEffect();

        virtual bool isWakidashi() const;
        virtual bool vf2E8(); // unknown
        virtual bool isBgmSync() const;

        // States
        static sFStateVirtualID_c<daEnKuribo_c> StateID_Born_Split1;
        static sFStateVirtualID_c<daEnKuribo_c> StateID_Born_Split2;
        static sFStateVirtualID_c<daEnKuribo_c> StateID_BlockAppear;
        static sFStateVirtualID_c<daEnKuribo_c> StateID_Down;
        static sFStateVirtualID_c<daEnKuribo_c> StateID_Auto_Walk;
        static sFStateVirtualID_c<daEnKuribo_c> StateID_Dokan_Down;
        static sFStateVirtualID_c<daEnKuribo_c> StateID_EatOut_Ready;
};
