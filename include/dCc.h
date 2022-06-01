#pragma once
#include <kamek.h>

// Forward declaration
class dActor_c;

// Documentation by Ninji and me
// Categories determine which actors an actor wants to hear from.
// For a collision between A and B to occur, both these conditions must be true:
// A.categoryBitfield & (1 << B.category) != 0
// B.categoryBitfield & (1 << A.category) != 0
struct ccCategory {
    enum Value {
        Player, // dAcPy_c, dJrClownA_c
        PlayerAtk, // dAcPy_c, daYoshi_c
        Yoshi, // daYoshi_c
        Entity, // most actors
        Balloon, // daEnHatenaBalloon_c
        Powerup, // powerups and collectables like coins and keys
        Projectile, // both player and enemy/boss ones
        BulletBill, // EN_CANNON_BULLET, EN_SEARCH_MAGNUM_KILLER
        GoalPole, // daEnGlPole_c
    };
};

// Documentation by Ninji and me
// Attacks determine which attack an actor is giving, in order for the opposing actor to pick the proper response
// If an actor is of Category 1, then its attack value is checked against the opposing actor's bitfield, and if they don't match no collision happens
// NOTE: For other categories, this is still checked depending on the sprite!
struct ccAttack {
    enum Value {
        None,
        Fireball,
        Iceball,
        Star,
        BreakIce, // Breaks ice on contact, set for all Spike Pillars
        Slide,
        KoopaFire, // Includes all Koopaling magic, Kamek magic and Bowser Jr/Bowser fire
        GroundPound,
        FencePunch,
        Entity, // Kills other enemies, used by Shells/Barrels and similar
        Penguin_Slide,
        SpinJump,
        Unk_12,
        PropellerDrill,
        Explosion, // Bob-ombs and similar
        Yoshi,
        YoshiTongue,
        PipeCannon,
        PropellerCarry, // Player carrying another while it's using the Propeller
        YoshiProjectile, // Hammers/Boomerangs
        YoshiFire,
        YoshiIce,
        SandPillar,
    };
};

struct ccMiscFlags {
    enum Value {
        Unk_1 = 1, // Set for players, has something to do with the flagpole
        Unk_2 = 2, // Set for Piranha Plants, Wigglers, Fuzzies and Jellybeams, unknown meaning
        IgnoreCollision = 4, // Set for bubbled players, ignores collision
        KillIce = 0x100, // Set for Thwomps, Kamek, Mega Urchins and Bramballs, thrown ice will not cause any damage if it touches this collision
        KillBombs = 0x200, // Set for Flamethrowers, explodes Bob-ombs (and destroys ice) if they touch the collision
    };
};

struct ccCollType {
    enum Value {
        Normal,
        Circle,
        TrapezoidUD,
        TrapezoidLR,
    };
};

class dCc_c {
    public:
        typedef void (*CollisionCallback)(dCc_c* self, dCc_c* other);

        struct CollisionInfo {
            float xDistToCenter;
            float yDistToCenter;
            float xDistToEdge;
            float yDistToEdge;
            u8 category;
            u8 attack;
            // 2 bytes padding
            u32 categoryBitfield;
            u32 attackBitfield;
            u16 miscFlags;
            // 2 bytes padding
            CollisionCallback callback;
        };

        dActor_c* owner;
        dActor_c* ignoreActor; // collisions with this actor are ignored in dCc_c::checkCollision
        u32 _C;

        dCc_c* prev;
        dCc_c* next;

        u32 canBounce; // set to 1 on Giant Wiggler body parts, if 0 Mario/Yoshi will not bounce and get hit instead
        CollisionInfo info;

        float trapezoidDistTL;
        float trapezoidDistTR;
        float trapezoidDistBL;
        float trapezoidDistBR;

        float displacementX[8]; // [i] holds the horizontal displacement due to collision with category i
        float displacementY[8]; // [i] holds the vertical displacement due to collision with category i
        VEC2 posLastCollision;

        u16 selfCatCheckResult;
        u16 otherAtkCheckResult;
        u16 selfAtkCheckResult;

        u8 collisionType;
        u8 chainlinkMode; // 0 = normal, 1 = front side, 2 = back side, 3 = ignores backfence
        u8 layer;
        u8 isDead; // set to 2 if actor is killed, 0 otherwise
        bool isLinked;
        // 1 byte padding
};
