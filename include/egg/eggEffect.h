#pragma once

#include <kamek.h>
#include <nw4r/ef/handle.h>
#include <nw4r/math/types.h>
#include <nw4r/ut/color.h>
#include <rvl/mtx/mtx.h>

namespace EGG {

class ExEffectParam {
    public:
        enum EStatus {
            LIFE_SET = 0x1,
            EMIT_RATIO_SET = 0x2,
            EMIT_INTERVAL_SET = 0x4,
            EMIT_DIV_SET = 0x8,
            VEL_RANDOM_SET = 0x10,
            VEL_POWER_YAXIS_SET = 0x20,
            VEL_POWER_RADIATION_DIR_SET = 0x40,
            VEL_POWER_SPEC_DIR_SET = 0x80,
            VEL_POWER_SPEC_DIR_ADD_SET = 0x100,
            VEL_SPEC_DIR_SET = 0x200,
            VEL_SPEC_DIR_ADD_SET = 0x400,
            COLOR_SET = 0x1000,
            COLORREG_1_SET = 0x2000,
            COLORREG_2_SET = 0x4000,
            COLORREG_3_SET = 0x8000,
            COLORREG_4_SET = 0x10000,
            DEFAULT_SIZE_SET = 0x20000,
            SIZE_SET = 0x40000,
            DEFAULT_ROT_SET = 0x80000,
            ROT_SET = 0x100000,
            EMITTER_SIZE_SET = 0x10000000,
            UNK_20000000 = 0x20000000,
            LOCAL_SCALE_SET = 0x40000000,
        };

        void* vtable;
        u32 flags;
        u32 _8; // something to do with flags
        u16 life;
        // 2 bytes padding

        float emitRatio;
        u16 emitInterval;
        u16 emitDiv;
        s8 initVelocityRandom;
        // 3 bytes padding

        float velPowerYAxis;
        float velPowerRadiationDir;
        float velPowerSpecDir;
        float velPowerSpecDirAdd;
        VEC3 velSpecDir;
        VEC3 velSpecDirAdd;

        nw4r::ut::Color color;
        nw4r::ut::Color registerColors[4];

        nw4r::math::VEC2 defaultScale;
        nw4r::math::VEC2 scale;
        VEC3 defaultRot;
        VEC3 rot;
        VEC3 emitterSize;
        VEC3 localScale;
};

class Effect {
    public:
        void* vtable;
        char name[0x20];
        u32 creatorId; // must always be zero
        u32 flags; // &1 = has translation, &2 = matrix set, &4 = ??
        VEC3 scale;
        VEC3 translate;
        MTX34 matrix;
        nw4r::ef::HandleBase handle;
        ExEffectParam exParams;
};

} // namespace EGG
