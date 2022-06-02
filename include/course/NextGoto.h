// Sources: Reggie, RoadRunnerWMC, B1, https://github.com/Newer-Team/NewerSMBW/blob/no-translations/Kamek/include/dCourse.h
#include <kamek.h>

struct EntranceType {
    enum Value {
        Normal,
        Normal1,
        Door,
        PipeUp,
        PipeDown,
        PipeLeft,
        PipeRight,
        Fall,
        GroundPound,
        Slide,
        Swim,
        Normal11,
        Normal12,
        Normal13,
        Invisible,
        Invisible15,
        MiniPipeUp,
        MiniPipeDown,
        MiniPipeLeft,
        MiniPipeRight,
        JumpRight,
        Vine,
        PipeForward,
        BossStand,
        JumpLeft,
        BossJumpRight,
        BossFallRight,
        Door27,
    };
};

struct EntranceFlag {
    enum Value {
        ConnectedPipeExit = 0x1,
        Unknown2 = 0x2,
        ForwardPipe = 0x4,
        ConnectedPipe = 0x8,
        SpawnHalfTileLeft = 0x40,
        NonEnterable = 0x80,
        WarpSecretExit = 0x100, // Custom
        DiscardProgressOnWarp = 0x200, // Custom
    };
};

struct NextGoto {
    u16 x;
    u16 y;
    u8 _4; // unused?
    u8 destMapNode; // custom
    u8 destWorld; // custom
    u8 destLevel; // custom
    u8 id;
    u8 destArea;
    u8 destId;
    u8 type;
    u8 _C; // unused?
    u8 zoneId;
    u8 layer;
    u8 pathId; // for connected pipes
    u16 flags;
    bool leaveStage;
    u8 exitDirection; // for connected pipes
};
