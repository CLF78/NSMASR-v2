#pragma once
#include <kamek.h>

enum LevelCompletion {
    COND_COIN1 = 0x1,
    COND_COIN2 = 0x2,
    COND_COIN3 = 0x4,
    COND_COIN_ALL = COND_COIN1 | COND_COIN2 | COND_COIN3,
    COND_NORMAL = 0x10,
    COND_SECRET = 0x20,
    COND_EXIT_ALL = COND_NORMAL | COND_SECRET,
    COND_SG_NORMAL = 0x80,
    COND_SG_SECRET = 0x100,
    COND_SG_ALL = COND_SG_NORMAL | COND_SG_SECRET,
};

enum SaveFlags {
    SAVE_NEW = 0x1,
    SAVE_GAME_COMPLETE = 0x2,
    SAVE_ALL_EXITS = 0x4,
    SAVE_ALL_STAR_COINS = 0x8,
    SAVE_ALL_STAR_COINS_W9 = 0x10,
    SAVE_EVERYTHING_TRULY_DONE = 0x20,
    SAVE_NO_SUPER_GUIDE = 0x40
};


class dMj2dGame_c {
    public:
        u8 version;                 // 0x00 (defaults to 14)
        u8 _1;                      // 0x01
        u8 bitfield;                // 0x02
        u8 currentWorld;            // 0x03
        u8 currentSubMap;           // 0x04
        u8 currentPathNode;         // 0x05
        bool ibaraNow;              // 0x06 (has something to do with W5 vines)
        bool switchOn;              // 0x07
        u8 _8;                      // 0x08
        u8 stockItemCounts[7];      // 0x09
        u8 toadLevelIdx[10];        // 0x10
        u8 playerContinues[4];      // 0x1A
        u8 playerCoins[4];          // 0x1E
        u8 playerLives[4];          // 0x22
        u8 playerFlags[4];          // 0x26
        u8 playerType[4];           // 0x2A
        u8 playerPowerup[4];        // 0x2E
        u8 worldsAvailable[10];     // 0x32
        u8 ambushCountdown[10][4];  // 0x3C
        u16 _64;                    // 0x64
        u16 creditsHighScore;       // 0x66
        u16 score;                  // 0x68
        u32 completions[10][42];    // 0x6C
        u8 hintMovieBought[70];     // 0x6FC
        u8 toadLocation[10];        // 0x742
        u8 _74C[10][4];             // 0x74C
        u8 _774[10][4];             // 0x774 (each element defaults to -1)
        u8 _79C[10][4];             // 0x79C (each element defaults to 2)
        u8 deathCounts[10][42];     // 0x7C4
        u8 deathCount34Switch;      // 0x968
        u8 pad[0x13];               // 0x969
        u32 checksum;               // 0x97C

        void setCollectCoin(int world, int level, u8 coins);
};
