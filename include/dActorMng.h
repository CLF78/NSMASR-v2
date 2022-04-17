#pragma once
#include <kamek.h>

class dActorMngField_c {
    public:
        u8 _0;
        bool _1; // used in remoconLineLift apparently?
        u8 _2;
};

class dActorMngSub_c {
    public:
        VEC3 position;
        u32 isFilled;
};

class dActorMng_c {
    public:
        dActorMngField_c fields[4]; // one per player

        u8 _C; // unused?
        u8 currentPlayerId;
        u8 nextPlayerId;
        bool _F; // ??

        u32 _10; // something with the subs
        u32 isExitingBossBattle; // messes with checkerboard blocks to turn their effects off for the cutscene to work

        void* daBossDemo;
        void* kazanMgr;

        u32 autoScroolSwichID; // unique id of instance taken from fBase (and no, this is not a typo)
        u32 stopSpawningEnemies; // used in ambushes to stop porcu-puffers and bullet bills from respawning
        u32 goombaZOrder; // gets taken by Goombas and Koopas and multiplied by 16 to set the z-order, value increases up to 15 and goes back to 0

        u32 liquidMovementDirection; // -1 = down, 0 = stopped, 1 = up
        u32 enableVolcanoEruptions;
        u32 _34; // some counter
        u32 lakituCloudsSink; // Only used in ambushes. If enabled and Mario hits the checkerboard blocks while on a cloud, the cloud will start moving downwards instead of upwards. The flag turns off automatically when opening the chest.
        u32 isEnteringAmbush; // used to disable spiny sensors while entering W2 ambushes

        u8 anotherPlayerId; // copied from nextPlayerId
        // 3 bytes padding

        float flagPoleXPosition; // used by the Lakitu cloud to prevent moving past the flagpole

        dActorMngSub_c subs[0x20]; // used by some sprites that rotate without a controller?
};
