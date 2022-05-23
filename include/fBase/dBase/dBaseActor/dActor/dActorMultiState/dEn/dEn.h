#pragma once
#include <kamek.h>
#include <fBase/dBase/dBaseActor/dActor/dActorMultiState/dActorMultiState.h>
#include <m/mTypes.h>
#include <state/sStateID.h>
#include <Boyon.h>
#include <dCc.h>
#include <dEnFumiCheck.h>
#include <dIceMng.h>

class dEn_c : public dActorMultiState_c {
    public:
        struct EntityDeathInfo {
            VEC2 speed;
            float yMaxSpeed;
            float yAccel;
            sStateID_c* state;
            u32 scoreType; // copy of related field in dEn_c
            int _18; // always -1, never read
            u8 direction;
            u8 playerId; // player who killed
            bool deathStateNotRun; // set to 0 if not killed or after the state has been switched
            // 1 byte padding
        };

        struct IceBitfield {
            enum Value {
                Unk1 = 1, // Something with shells sliding on expanding blocks, couldn't find a difference
                AltKillEffect = 2, // Spawns a different effect when spin-jumped on
                ChainlinkIce = 4, // Sets ice's chainlinkMode based on the appearsOnBackfence variable
                CoinBattleExtraSFX = 0x10, // Plays an extra sound effect if killed in coin battle
                KillWhenFrozenUnderwater = 0x10000,
                DestroyIceIfFrozenMidair = 0x20000, // Spawns a coin when destroyed
                NoPlayerDamage = 0x1000000,
            };
        };

        EntityDeathInfo deathInfo;

        u32 canBounce; // copied from the related field in dCc_c;
        u16 leaveScreen; // value 0/1, only used for Lakitu, if set Lakitu will stop throwing and leave the screen
        // 2 bytes padding

        u32 _43C; // completely unused

        // not sure what these do
        VEC3 someVelocity;
        VEC3 someVelocity2;
        u8 someDirection;
        u8 someDirection2;

        bool killed; // only set for Chain Chomps and actors that touch lava
        u8 _45B; // completely unused

        bool onQuicksand;
        bool immersedInLiquid;
        bool onIce;
        // 3 bytes padding

        s16 hopCount; // used on items/springs to determine how many hops the item does when spat out by Yoshi; also used by sprite 150 for some reason?
        u8 someAngleIdx; // used on cheep cheeps to determine angle??
        // 1 byte padding

        Boyon boyon;

        bool iceBallHitFromRight; // 1 if the iceball's direction was left else 0, no idea what this changes
        // 3 bytes padding

        dIceMng_c iceMng;
        u32 _4EC; // completely unused

        float ySpeedIncreaseBeforeEnteringWater;
        float yMaxSpeedBeforeEnteringWater;
        float fallSpeedBeforeEnteringWater;

        u32 iceBitfield;

        // a bunch of timers, used creatively by different actors but mostly to delay state changes
        // automatically decremented by dEn_c::preExecute
        u16 someTimer;
        u16 someOtherTimer;

        u16 collisionTimer[4]; // indexed by playerId, delays the next collision with the specified player/yoshi

        u8 someCounter; // completely unused
        // 3 bytes padding

        u32 scoreType2; // same as the dActor_c field, but controls other combos like sliding/starring/shells/etc
        dEnFumiCheck_c fumiCheck;

        // fBase overrides
        virtual void postCreate(fBase_c::MAIN_STATE_e status);

        virtual int preExecute();
        virtual void postExecute(fBase_c::MAIN_STATE_e status);

        virtual int preDraw();

        virtual ~dEn_c();

        // dActor_c overrides
        virtual void kill(); // unofficial name

        virtual void setEatTongue(dActor_c* eaterActor);
        virtual void setEatTongueOff(dActor_c* eaterActor);
        virtual void setEatSpitOut(dActor_c* eatenActor);

        virtual void calcEatInScale(dActor_c* eaterActor);

        virtual void yoganSplashEffect(const mVec3_c& pos, float scale);
        virtual void poisonSplashEffect(const mVec3_c& pos, float scale);

        // dActorMultiState_c overrides
        virtual void changeState(const sStateIDIf_c& state);

        // Damage check functions
        virtual bool EnDamageCheck(dCc_c* self, dCc_c* other);
        virtual bool PlDamageCheck(dCc_c* self, dCc_c* other);
        virtual bool YoshiDamageCheck(dCc_c* self, dCc_c* other);
        virtual bool EtcDamageCheck(dCc_c* self, dCc_c* other);

        // Collision handlers (names are unofficial)
        virtual void spriteCollision(dCc_c* self, dCc_c* other);
        virtual void playerCollision(dCc_c* self, dCc_c* other);
        virtual void yoshiCollision(dCc_c* self, dCc_c* other);

        // Collision callbacks
        virtual bool hitCallback_Star(dCc_c* self, dCc_c* other);
        virtual bool hitCallback_Slip(dCc_c* self, dCc_c* other);
        virtual bool hitCallback_Large(dCc_c* self, dCc_c* other); // unused?
        virtual bool hitCallback_Spin(dCc_c* self, dCc_c* other);
        virtual bool hitCallback_Rolling(dCc_c* self, dCc_c* other); // unused
        virtual bool hitCallback_WireNet(dCc_c* self, dCc_c* other);
        virtual bool hitCallback_HipAttk(dCc_c* self, dCc_c* other);
        virtual bool hitCallback_YoshiHipAttk(dCc_c* self, dCc_c* other);
        virtual bool hitCallback_Screw(dCc_c* self, dCc_c* other); // unused
        virtual bool hitCallback_PenguinSlide(dCc_c* self, dCc_c* other);
        virtual bool hitCallback_Cannon(dCc_c* self, dCc_c* other);
        virtual bool hitCallback_Shell(dCc_c* self, dCc_c* other);
        virtual bool hitCallback_Fire(dCc_c* self, dCc_c* other);
        virtual bool hitCallback_Ice(dCc_c* self, dCc_c* other);
        virtual bool hitCallback_YoshiBullet(dCc_c* self, dCc_c* other);
        virtual bool hitCallback_YoshiFire(dCc_c* self, dCc_c* other);

        // Kill callbacks
        virtual void setDeathInfo_Other(dActor_c* killingPlayer);
        virtual void setDeathInfo_Quake(int isNotMPGP);
        virtual void setDeathInfo_IceBreak();
        virtual void setDeathInfo_IceVanish();

        // Random functions
        virtual int isQuakeDamage();
        virtual void hitYoshiEat(dCc_c* self, dCc_c* other);

        // More kill callbacks because fuck ordering
        virtual void setDeathSound_HipAttk();
        virtual void setDeathSound_Fire();
        virtual void setDeathSound_Slip(dActor_c* killingPlayer);
        virtual void setDeathSound_Spin();
        virtual void setDeathSound_Rolling();

        // State functions
        virtual void initializeState_DieFumi();
        virtual void executeState_DieFumi();
        virtual void finalizeState_DieFumi();
        virtual void initializeState_DieFall();
        virtual void executeState_DieFall();
        virtual void finalizeState_DieFall();
        virtual void initializeState_DieBigFall();
        virtual void executeState_DieBigFall();
        virtual void finalizeState_DieBigFall();
        virtual void initializeState_DieSmoke();
        virtual void executeState_DieSmoke();
        virtual void finalizeState_DieSmoke();
        virtual void initializeState_DieYoshiFumi();
        virtual void executeState_DieYoshiFumi();
        virtual void finalizeState_DieYoshiFumi();
        virtual void initializeState_DieIceVanish();
        virtual void executeState_DieIceVanish();
        virtual void finalizeState_DieIceVanish();
        virtual void initializeState_DieGoal();
        virtual void executeState_DieGoal();
        virtual void finalizeState_DieGoal();
        virtual void initializeState_DieOther();
        virtual void executeState_DieOther();
        virtual void finalizeState_DieOther();
        virtual void initializeState_EatIn();
        virtual void executeState_EatIn();
        virtual void finalizeState_EatIn();
        virtual void initializeState_EatNow();
        virtual void executeState_EatNow();
        virtual void finalizeState_EatNow();
        virtual void initializeState_EatOut();
        virtual void executeState_EatOut();
        virtual void finalizeState_EatOut();
        virtual void initializeState_HitSpin();
        virtual void executeState_HitSpin();
        virtual void finalizeState_HitSpin();
        virtual void initializeState_Ice();
        virtual void executeState_Ice();
        virtual void finalizeState_Ice();

        // Random stuff i guess
        virtual void fumidamageEffect(const mVec3_c* pos);
        virtual void hipatkEffect(const mVec3_c* pos);
        virtual void playEnemyDownSound2(); // unofficial name
        virtual void add2ToYSpeed(); // unofficial name
        virtual bool checkDispIn();
        virtual void setWaterSpeed();
        virtual void setDamage(dActor_c* collidedActor);
        virtual void boyonBegin();
        virtual void calcBoyonScale();
        virtual bool createIceActor(); // unofficial name
        virtual void setIceAnm();
        virtual void vf234(); // unknown
        virtual void setsAfterIceState(); // unofficial name

        // Funsui stuff
        virtual void beginFunsui();
        virtual void endFunsui();
        virtual bool isFunsui() const;
        virtual bool checkComboClap(int comboCount);

        // Reactions to being hit by a player/mini player/yoshi: physics, score, sfx and gfx
        virtual void FumiJumpSet(dActor_c* collidedActor);
        virtual void FumiScoreSet(dActor_c* collidedActor);
        virtual void MameFumiJumpSet(dActor_c* collidedActor);
        virtual void YoshiFumiJumpSet(dActor_c* collidedActor);
        virtual void YoshiFumiScoreSet(dActor_c* collidedActor);
        virtual void fumiSE(dActor_c* collidedActor);
        virtual void fumiEffect(dActor_c* collidedActor);
        virtual void spinfumiSE(dActor_c* collidedActor);
        virtual void spinfumiEffect(dActor_c* collidedActor);
        virtual void mamefumiSE(dActor_c* collidedActor);
        virtual void mamefumiEffect(dActor_c* collidedActor);
        virtual void yoshifumiSE(dActor_c* collidedActor);
        virtual void yoshifumiEffect(dActor_c* collidedActor);

        // States
        static sFStateVirtualID_c<dEn_c> StateID_DieFumi;
        static sFStateVirtualID_c<dEn_c> StateID_DieFall;
        static sFStateVirtualID_c<dEn_c> StateID_DieBigFall;
        static sFStateVirtualID_c<dEn_c> StateID_DieSmoke;
        static sFStateVirtualID_c<dEn_c> StateID_DieYoshiFumi;
        static sFStateVirtualID_c<dEn_c> StateID_DieIceVanish;
        static sFStateVirtualID_c<dEn_c> StateID_DieGoal;
        static sFStateVirtualID_c<dEn_c> StateID_DieOther;
        static sFStateVirtualID_c<dEn_c> StateID_EatIn;
        static sFStateVirtualID_c<dEn_c> StateID_EatNow;
        static sFStateVirtualID_c<dEn_c> StateID_EatOut;
        static sFStateVirtualID_c<dEn_c> StateID_HitSpin;
        static sFStateVirtualID_c<dEn_c> StateID_Ice;
};
