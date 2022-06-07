#include <kamek.h>
#include <dBg.h>
#include <m/mTypes.h>

class dBg_ctr_c {
    public:
        typedef bool (*checkF)(dActor_c* self, dActor_c* other);
        typedef bool (*checkH)(dActor_c* self, dActor_c* other);
        typedef bool (*checkW)(dActor_c* self, dActor_c* other, u8 direction);

        typedef void (*callbackF)(dActor_c* self, dActor_c* other);
        typedef void (*callbackH)(dActor_c* self, dActor_c* other);
        typedef void (*callbackW)(dActor_c* self, dActor_c* other, u8 direction);

        dActor_c* owner;

        dBg_ctr_c* prev;
        dBg_ctr_c* next;

        dBc_c* triggeredBelowSensor;
        dBc_c* triggeredAboveSensor;
        dBc_c* triggeredAdjSensor;
        dBc_c* triggeredPlayerFenceSensors[4]; // used by players on moving chainlinks and vines
        dBc_c* triggeredPlayerWallSlideSensors[4]; // used by players when wall sliding

        dActor_c* carryingActor; // collisions with this actor are ignored

        u32 isCalced;

        callbackF belowCallback;
        callbackH aboveCallback;
        callbackW adjCallback;

        checkF belowCheckFunc;
        checkH aboveCheckFunc;
        checkW adjCheckFunc;

        mVec2_c lastPos;
        mVec2_c calcedPos[4];

        float offsetLeft; // used for circles as well
        float offsetTop; // used for circles as well
        float offsetRight;
        float offsetBottom;

        float diameter; // only used for circles

        mVec3_c ownerPos;
        mVec2_c distanceFromOwner; // ??
        mVec2_c prevDistanceFromOwner; // ??
        mVec3_c displacement; // ??

        s16* rotationPtr;
        s16 rotation;
        s16 rotationDelta;
        s16 rotationDelta2; // no idea why this is a thing
        // 2 bytes padding

        u32 isRound;
        u32 _CC; // value 0-10, maybe a category sort of thing??
        u32 flags; // TODO document
        s32 _D4;
        u32 _D8; // a bitfield

        bool linked;

        u8 chainlinkMode;
        u8 layer;
        // 1 byte padding

        s32 id;

        static dBg_ctr_c* mEntryN;
        static dBg_ctr_c* mEntryB;
};
