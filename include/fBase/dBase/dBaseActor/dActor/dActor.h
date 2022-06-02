#include <kamek.h>
#include <fBase/dBase/dBaseActor/dBaseActor.h>
#include <m/mTypes.h>
#include <dBc.h>
#include <dCc.h>
#include <dPropelParts.h>
#include <dRc.h>

struct Kind {
    enum Value {
        Normal,
        Player,
        Yoshi,
        Entity,
    };
};

class dActor_c : public dBaseActor_c {
    public:
        int carryingPlayerId; // -1 if not being carried
        u32 carryingFlags; // &1 = thrown, &2 = being carried
        u8 carryingDirection;
        // 3 bytes padding

        u32 comboCount; // used by Yoshi Fire and Shells to keep track of combos, value 0-7

        u32 _138; // unused?
        u32 _13C; // set to 0 in constructor, never used again?
        float _140; // set to 1.0 in constructor, never used again?
        u32 _144; // unused?

        dCc_c collisionCheck;
        dBc_c bgCheck;
        dRc_c rideCheck;

        VEC2 _310; // related to zone borders maybe?
        VEC2 visibleAreaSize; // doubled
        VEC2 visibleAreaOffset;
        VEC2 _328;
        VEC2 maxBoundDistance; // from zone edge
        float destroyBoundDistanceTop;
        float destroyBoundDistanceBottom;
        float destroyBoundDistanceLeft;
        float destroyBoundDistanceRight;

        u8 direction;
        u8 zoneId;
        u8 _34A; // a bitfield related to collision
        // 1 byte padding

        u8* byteStorage; // links to dActorCreateMng_c
        u16* shortStorage; // links to dActorCreateMng_c
        u8 eventNums[2];
        // 2 bytes padding
        u64 eventMask;

        u32 _360; // used creatively by various actors
        u16 spawnInfoFlags;
        bool killIfDisabled; // something with execStop
        // 1 byte padding

        u32 eaterActorId; // unique id of actor who ate this one
        u8 eatState; // 0 = normal, 2 = eaten, 4 = spat out
        u8 eatSpitType; // 4 = fireball, 5 = iceball
        // 2 bytes padding
        VEC3 scaleBeforeBeingEaten;

        u32 scoreType; // 0 = 200 points, 1 = 1000 points, 2 = no points
        u32 lookAtMode;
        u32 _384; // a bitfield, only used by koopalings apparently

        dPropelParts_c* carryPropelActor;
        u8 kind;
        s8 playerNo;
        u8 disableMask;
        u8 layerId;
        bool deleteForever;
        bool appearsOnBackfence;
        u8 _392[2];

        dActor_c();

        virtual int preCreate();
        virtual void postCreate(fBase_c::MAIN_STATE_e status);

        virtual int preDelete();
        virtual void postDelete(fBase_c::MAIN_STATE_e status);

        virtual int preExecute();
        virtual void postExecute(fBase_c::MAIN_STATE_e status);

        virtual int preDraw();
        virtual void postDraw(fBase_c::MAIN_STATE_e status);

        virtual ~dActor_c();

        virtual char* getKindString() const;

        virtual bool ActorDrawCullCheck();

        virtual void kill(); // unofficial name
        virtual void vf68(); // unknown

        virtual s8* getPlrNo();
        virtual VEC2 getLookatPos() const;
        virtual bool isSpinLiftUpEnable();

        virtual void setSpinLiftUpActor(dActor_c* carryingActor);
        virtual void setCarryFall(dActor_c* carryingActor, int unk);

        virtual void setEatTongue(dActor_c* eaterActor);
        virtual void setEatTongueOff(dActor_c* eaterActor);
        virtual void setEatMouth(dActor_c* eatenActor);
        virtual void setEatSpitOut(dActor_c* eatenActor);
        virtual bool setEatScore(dActor_c* eaterActor); // unofficial name
        virtual void eatMove(dActor_c* eaterActor);

        virtual void removeCc();
        virtual void reviveCc();
        virtual void restoreScale(); // unofficial name

        virtual void calcSpitOutPos(dActor_c* eaterActor);
        virtual float calcEatScaleRate(dActor_c* eaterActor);
        virtual void calcEatInScale(dActor_c* eaterActor);

        virtual void endOfLevelClear(); // unofficial name

        virtual void vfB4(); // unknown
        virtual void vfB8(); // unknown
        virtual void vfBC(); // unknown
        virtual void vfC0(); // unknown
        virtual void vfC4(); // unknown

        virtual void waterSplashEffect(const mVec3_c& pos, float scale);
        virtual void yoganSplashEffect(const mVec3_c& pos, float scale);
        virtual void poisonSplashEffect(const mVec3_c& pos, float scale);

        bool checkZoneBoundaries(u32 flags); // unofficial name, &2 = does not delete offscreen actors, &4 = only checks zone boundaries &8 = checks ride output instead of bounds
};
