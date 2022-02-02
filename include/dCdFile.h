#pragma once

#include <kamek.h>

// Also contains various structs and enums used in the course files

enum EntranceType {
    ENTRANCE_NORMAL,
    ENTRANCE_NORMAL_1,
    ENTRANCE_DOOR,
    ENTRANCE_PIPE_UP,
    ENTRANCE_PIPE_DOWN,
    ENTRANCE_PIPE_LEFT,
    ENTRANCE_PIPE_RIGHT,
    ENTRANCE_FALLING,
    ENTRANCE_GROUND_POUND,
    ENTRANCE_SLIDING,
    ENTRANCE_SWIMMING,
    ENTRANCE_NORMAL_B,
    ENTRANCE_NORMAL_C,
    ENTRANCE_NORMAL_D,
    ENTRANCE_INVISIBLE,
    ENTRANCE_INVISIBLE_F,
    ENTRANCE_MINI_PIPE_UP,
    ENTRANCE_MINI_PIPE_DOWN,
    ENTRANCE_MINI_PIPE_LEFT,
    ENTRANCE_MINI_PIPE_RIGHT,
    ENTRANCE_JUMP_RIGHT,
    ENTRANCE_VINE,
    ENTRANCE_PIPE_FORWARD,
    ENTRANCE_BOSS_STAND,
    ENTRANCE_JUMP_LEFT,
    ENTRANCE_BOSS_JUMP_RIGHT,
    ENTRANCE_BOSS_FALL_RIGHT,
    ENTRANCE_DOOR_1B,
};

enum EntranceFlags {
    FLAG_CONNECTED_PIPE_EXIT = 0x1,
    FLAG_UNKNOWN_2 = 0x2,
    FLAG_FORWARD_PIPE = 0x4,
    FLAG_CONNECTED_PIPE = 0x8,
    FLAG_SPAWN_HALF_TILE_LEFT = 0x40,
    FLAG_NON_ENTERABLE = 0x80,
    FLAG_WARP_SECRET_EXIT = 0x100, // custom
};

typedef struct {
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
} NextGoto;
