#pragma once
#include <kamek.h>
#include <fBase/dBase/dBaseActor/dActor/dActor.h>
#include <fBase/dBase/dBaseActor/dActor/dActorMultiState/dEn/daEnKuriboBase/daEnKuriboBase.h>
#include <m/m3d/anmchr.h>
#include <m/m3d/anmtexpat.h>
#include <m/m3d/mdl.h>
#include <nw4r/g3d/res/resfile.h>
#include <state/sStateID.h>
#include <dBc.h>
#include <dCc.h>

class daEnPataKuribo_c : public daEnKuriboBase_c {
    public:
        nw4r::g3d::ResFile wingRes;
        m3d::mdl_c wingMdl;
        m3d::anmChr_c wingAnmChr;

        u16 turningTimer; // value set to 64 after turning
        u16 jumpTimer; // value 0-3, increased every hop, jumps when value is 0

        u32 _8DC; // unused
        u32 hasWings;

        m3d::anmTexPat_c* customAnmTexPat; // custom field, originally unused

        // fBase overrides
        virtual ~daEnPataKuribo_c();

        // dBaseActor overrides
        virtual void finalUpdate();

        // dEn overrides
        virtual bool hitCallback_Ice(dCc_c* self, dCc_c* other);

        virtual void playEnemyDownSound2(); // unofficial name
        virtual bool createIceActor(); // unofficial name
        virtual void setsAfterIceState(); // unofficial name

        virtual void beginFunsui();
        virtual void endFunsui();
        virtual bool isFunsui() const;

        // daEnKuriboBase overrides
        virtual void calcModel();
        virtual void reactFumiProc(dActor_c* killingActor);
        virtual void reactSpinFumiProc(dActor_c* killingActor); // unofficial name
        virtual void reactYoshiFumiProc(dActor_c* killingActor); // unofficial name

        virtual void loadWingModel(); // unofficial name
        virtual void drawModel();

        virtual void initialize();
        virtual void setTurnState(); // unofficial name
        virtual void vf2D0(dActor_c* collidingActor); // unknown

        virtual void setWalkSpeed();
        virtual void updateModel(); // unofficial name
        virtual void walkEffect();

        virtual bool isWakidashi() const;
        virtual bool vf2E8(); // unknown
        virtual bool isBgmSync() const;

        // States
        static sFStateVirtualID_c<daEnPataKuribo_c> StateID_Pata_Walk;
        static sFStateVirtualID_c<daEnPataKuribo_c> StateID_Pata_Turn;
};
