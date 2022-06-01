#pragma once
#include <kamek.h>

// Forward declarations
class dActor_c;
class dBg_ctr_c;
class dRc_c;

struct SensorFlags {
    enum Type {
        Point,
        Line,
    };

    enum Value {
        Unk_2 = 2, // ??
        IgnoreSimpleColl = 4, // ??
        Unk_8 = 8, // Can enter pipe (?)
        Unk_10 = 0x10, // Related to ice (?)
        Unk_20 = 0x20, // Related to ice (?)
        Unk_40 = 0x40, // ??
        Unk_80 = 0x80, // ??
        Unk_100 = 0x100, // ??
        IgnoreMouseHole = 0x200,
        Unk_400 = 0x400, // ??
        Unk_800 = 0x800, // ??
        NoQuicksand = 0x1000,
        Unk_2000 = 0x2000, // Related to fences (?)
        BreakBlock = 0x4000, // Used by Spike Balls
        JumpDai = 0x8000,
        Unk_10000 = 0x10000, // ??
        Coin1 = 0x20000,
        Coin2 = 0x40000, // Difference with 0x20000?
        CoinOutline = 0x80000,
        ActivateQuestion = 0x100000,
        ActivateDonuts = 0x200000,
        ActivateBrick = 0x400000,
        BreakBrick = 0x800000,
        Unk_1000000 = 0x1000000, // ??
        Unk_2000000 = 0x2000000, // ??
        Unk_4000000 = 0x4000000, // Something related to hitting blocks (?)
        Unk_8000000 = 0x8000000, // ??
        KeepMomentum = 0x10000000, // Used by Giant Spike Balls to keep moving
        Unk_20000000 = 0x20000000, // ??
        Unk_40000000 = 0x40000000, // ??
        NoCollision = 0x80000000,
    };
};

struct SensorOutputFlags {
    enum Value {
        AboveMask = 0xFC000000,
        BelowMask = 0x3FFE000,
        AdjacentMask = 0x1FFF,
    };
};

struct SakaType {
    enum Value {
        None,
        Solid,
        Slope,
        Unk_3,
    };
};

// Represents the first 4 bytes of the tileset behaviour
struct UnitType {
    enum Value {
        None = 0,
        Solid = 1,
        Coin = 2,
        QuestionBlock = 4,
        ExplodableBlock = 8,
        BreakableBlock = 0x10,
        Slope = 0x20,
        ReverseSlope = 0x40,
        Unk_80 = 0x80, // Unused?
        Unk_100 = 0x100, // Unused?
        Water = 0x200, // ??
        ClimbableFence = 0x400,
        PartialSolid = 0x800,
        Spike = 0x1000,
        SolidOnBottom = 0x2000,
        Unk_4000 = 0x4000, // Unused?
        SolidOnTop = 0x8000,
        Pipe = 0x10000,
        DonutBlock = 0x20000,
        Unk_40000 = 0x40000, // Unused?
        Ledge = 0x80000,
        FakeBlockMaybe = 0x100000, // ??
        Unk_200000 = 0x200000, // Unused?
        Unk_400000 = 0x400000, // Unused?
        Unk_800000 = 0x800000, // Unused?
        Unk_1000000 = 0x1000000, // Unused?
        Meltable = 0x2000000,
        Unk_4000000 = 0x4000000, // Unused?
        Unk_8000000 = 0x8000000, // Unused?
        Unk_10000000 = 0x10000000, // Unused?
        Unk_20000000 = 0x20000000, // Unused?
        Unk_40000000 = 0x40000000, // Unused?
        Unk_80000000 = 0x80000000, // Unused?
    };
};

struct BgDamageFlag {
    enum Value {
        None = 0,
        SpikeLeft = 1,
        SpikeRight = 2,
        SpikeUp = 4,
        SpikeDown = 8,
        SpikeLongDown = 0x10,
        SpikeLongDown2 = 0x20,
        SpikeSingleDown = 0x40,
        Unk_80 = 0x80,
    };
};

// Sensors
struct sensorBase_s {
    u32 flags;
};

struct pointSensor_s : sensorBase_s {
    s32 x, y;
};

struct lineSensor_s : sensorBase_s {
    s32 lineA, lineB, distanceFromCenter;
};

// The actual class
class dBc_c {
    public:
        dBc_c* next; // custom field, originally an unused vtable

        dActor_c* owner;
        sensorBase_s* belowSensor;
        sensorBase_s* aboveSensor;
        sensorBase_s* adjacentSensor;

        VEC3* pos;
        VEC3* lastPos;
        VEC3* speed;
        VEC3 specialSpeedOffset;
        VEC2 speedDelta;
        VEC2 ridePos;
        VEC2 _3C;

        // VEC2 maybe?
        u32 _44;
        u32 _48;

        float initialX;

        dRc_c* rc;

        u32 _54;

        dBg_ctr_c* belowCtr;
        dBg_ctr_c* aboveCtr;
        dBg_ctr_c* adjacentCtrLast;
        dBg_ctr_c* adjacentCtrs[2];

        dBc_c* _6C;
        dBc_c* _70;
        dBc_c* _74;
        dBc_c* linkW_bc[2];
        dBg_ctr_c* linkW_ctr[2];

        u32 output;
        u32 prevOutput;

        u32 lastUnitType;
        u32 _94;

        u8 playerId;
        u8 playerNo;

        u16 lastX;
        u16 lastY;
        // 2 bytes padding

        u32 tileBelowProps;
        u8 tileBelowSubType;
        u8 lastTileBelowSubType;
        // 2 bytes padding

        u32 tileAboveProps;
        u8 tileAboveSubType;
        u8 lastTileAboveSubType;
        // 2 bytes padding

        u32 adjacentTileProps[2];
        u8 adjacentTileSubTypes[2];
        u8 lastTileAdjacentSubTypes[2];

        u8 _BC; // &4 = something with slopes (?), &8 allows entering mini pipes?

        u8 currentSlopeType;
        s16 currentSlopeAngle;
        u8 currentFlippedSlopeType;
        s16 currentFlippedSlopeAngle;
        // 1 byte padding
        u32 _C4;
        u16 currentAdjacentSlopeAngle;
        // 2 bytes padding

        u32 currentFenceType; // 0 = null, 1 = ladder, 2 = fence

        dBg_ctr_c* _D0;

        // VEC3 maybe?
        float _D4;
        float _D8;
        float _DC;

        u8 bgDamageFlag;
        s8 maxTouchedSpikeType;

        u8 currentSlopeDirection;

        bool _E3;
        bool onGround; // ??

        u8 chainlinkMode; // see dCc_c
        // 2 bytes padding

        u8* layerPtr;
        u8 layer;

        bool enteredPipeIsMini;
        // 2 bytes padding
};
