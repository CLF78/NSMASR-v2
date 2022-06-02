#include <kamek.h>
#include <fBase/dBase/dBaseActor/dActor/dActor.h>

class dIceMng_c {
    public:
        int iceActorCount;
        int iceTimers[2];

        u32 isFrozen;
        u32 iceActorStartingStateParsed; // 0/9+ = Land 1/6 = Freeze, 2 = Air, 3 = Fall, 4/5 = YoganDive/Sink, 7 = Cover, 8 = Hop
        u32 iceMeltingState; // 1 = frozen, 2 = shaking, 3 = broken
        u32 iceBehaviour; // 0 = unfreeze after delay, 1 = kill immediately, 3 = kill immediately and give coin

        /* Timer Types:
        0 = 480 frames (default, begins shaking at 90 frames)
        1 = 15 frames (actor unfreezes immediately, begins shaking at 10 frames)
        2 = 140 frames (used by cheep cheeps and urchins, begins shaking at 60 frames)
        3 = 60 frames (used by lakitu, begins shaking at 10 frames)
        4 = 30 frames (used by bloopers, begins shaking at 15 frames)
        5 = 300000 frames (unused, begins shaking at 1 frame) */
        u32 timerTypeCopy; // what is the point of this?
        u32 timerType;

        /* How this shit works (see above for values):
        If the starting state is 1/3/7/8, it is returned as is
        If the enemy is not immersed and has a ground sensor, it will use state 2 if in midair, else 1
        If the enemy is immersed, the immersed state is returned
        If the starting state is 2 and the timerType is 1, state 1 is used instead */
        u32 iceActorStartingState;
        u32 iceActorStartingStateImmersed;

        u32 permFreeze; // does not mean it cannot be broken!
        u32 playerId; // player who froze the entity

        u32 iceActorIDs[12];
        dActor_c* owner;
};
