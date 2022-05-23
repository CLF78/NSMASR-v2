#pragma once
#include <kamek.h>
#include <fBase/dBase/dBaseActor/dActor/dActorMultiState/dEn/daEnKuriboBase/daEnKuriboBase.h>
#include <m/m3d/anmtexpat.h>

// NOTE: this is the unused Micro Goomba actor!
class daEnMameKuribo_c : public daEnKuriboBase_c {
    public:
        m3d::anmTexPat_c* customAnmTexPat; // custom field, originally unused

        // fBase overrides
        virtual ~daEnMameKuribo_c();

        // dBaseActor overrides
        virtual void finalUpdate();

        // dEn overrides
        virtual bool PlDamageCheck(dCc_c* self, dCc_c* other);

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
        virtual void setWalkSpeed();
        virtual void updateModel(); // unofficial name
        virtual void walkEffect();

        virtual bool isWakidashi() const;
        virtual bool vf2E8(); // unknown
        virtual bool isBgmSync() const;
};
