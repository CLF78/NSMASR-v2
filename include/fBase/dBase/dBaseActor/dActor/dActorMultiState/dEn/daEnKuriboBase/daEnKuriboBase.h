#pragma once
#include <kamek.h>
#include <fBase/dBase/dBaseActor/dActor/dActor.h>
#include <fBase/dBase/dBaseActor/dActor/dActorMultiState/dEn/dEn.h>
#include <m/m3d/anmchr.h>
#include <m/m3d/anmtexpat.h>
#include <m/m3d/mdl.h>
#include <m/mEf/levelEffect.h>
#include <m/mEf/levelOneEffect.h>
#include <nw4r/g3d/res/resanmpat.h>
#include <nw4r/g3d/res/resfile.h>
#include <state/sStateID.h>
#include <dCc.h>
#include <dHeapAllocator.h>

class daEnKuriboBase_c : public dEn_c {
    public:
        dHeapAllocator_c allocator;

        nw4r::g3d::ResFile resFile;
        m3d::mdl_c mdl;
        m3d::anmChr_c anmChr;
        nw4r::g3d::ResAnmTexPat resPat;
        m3d::anmTexPat_c anmTexPat;

        float zOffset;
        u32 isFrozen;
        float savedSpeed;

        mEf::levelEffect_c levelEffect;
        mEf::levelOneEffect_c levelOneEffect;

        u16 checkZoneBoundParam;
        // 2 bytes padding

        // fBase overrides
        virtual int create();
        virtual int doDelete();
        virtual int execute();
        virtual int draw();

        virtual ~daEnKuriboBase_c();

        // dBaseActor overrides
        virtual void finalUpdate();

        // dEn overrides
        virtual void spriteCollision(dCc_c* self, dCc_c* other);
        virtual void playerCollision(dCc_c* self, dCc_c* other);
        virtual void yoshiCollision(dCc_c* self, dCc_c* other);

        virtual void initializeState_DieOther();
        virtual void executeState_DieOther();
        virtual void finalizeState_DieOther();

        virtual void playEnemyDownSound2(); // unofficial name
        virtual void setDamage(dActor_c* collidedActor);

        virtual void beginFunsui();
        virtual void endFunsui();
        virtual bool isFunsui() const;

        // New virtuals
        virtual void initializeState_Walk();
        virtual void executeState_Walk();
        virtual void finalizeState_Walk();
        virtual void initializeState_Turn();
        virtual void executeState_Turn();
        virtual void finalizeState_Turn();
        virtual void initializeState_TrplnJump();
        virtual void executeState_TrplnJump();
        virtual void finalizeState_TrplnJump();

        virtual void calcModel();
        virtual void reactFumiProc(dActor_c* killingActor);
        virtual void vf2AC(); // unknown
        virtual void reactSpinFumiProc(dActor_c* killingActor); // unofficial name
        virtual void reactYoshiFumiProc(dActor_c* killingActor); // unofficial name

        virtual void createModel();
        virtual void loadModel(); // unofficial name
        virtual void loadWingModel(); // unofficial name
        virtual void drawModel();

        virtual void initialize();
        virtual void setTurnState(); // unofficial name
        virtual void vf2D0(dActor_c* collidingActor); // unknown

        virtual void setWalkSpeed();
        virtual void playWalkAnim(); // unofficial name
        virtual void updateModel(); // unofficial name
        virtual void walkEffect();

        virtual bool isWakidashi() const;
        virtual bool vf2E8(); // unknown
        virtual bool isBgmSync() const;

        // States
        static sFStateVirtualID_c<daEnKuriboBase_c> StateID_Walk;
        static sFStateVirtualID_c<daEnKuriboBase_c> StateID_Turn;
        static sFStateVirtualID_c<daEnKuriboBase_c> StateID_TrplnJump;
        static sFStateVirtualID_c<daEnKuriboBase_c> StateID_DieOther;
};
