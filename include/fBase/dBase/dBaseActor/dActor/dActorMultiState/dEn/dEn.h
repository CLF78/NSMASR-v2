#pragma once
#include <kamek.h>
#include <fBase/dBase/dBaseActor/dActor/dActorMultiState/dActorMultiState.h>
#include <state/sStateID.h>
#include <Boyon.h>
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

        uint scoreType2; // same as the dActor_c field, but controls other combos like sliding/starring/shells/etc
        dEnFumiCheck_c fumiCheck;
};
