#include <kamek.h>
#include <nw4r/ef/handle.h>
#include <nw4r/math/types.h>
#include <nw4r/ut/color.h>

namespace EGG {

class ExEffectParam {
    public:
        enum EStatus {
            LifeSet = 0x1,
            EmitRatioSet = 0x2,
            EmitIntervalSet = 0x4,
            EmitDivSet = 0x8,
            VelRandomSet = 0x10,
            VelPowerYAxisSet = 0x20,
            VelPowerRadiationDirSet = 0x40,
            VelPowerSpecDirSet = 0x80,
            VelPowerSpecDirAddSet = 0x100,
            VelSpecDirSet = 0x200,
            VelSpecDirAddSet = 0x400,
            ColorSet = 0x1000,
            ColorReg1Set = 0x2000,
            ColorReg2Set = 0x4000,
            ColorReg3Set = 0x8000,
            ColorReg4Set = 0x10000,
            DefaultSizeSet = 0x20000,
            SizeSet = 0x40000,
            DefaultRotSet = 0x80000,
            RotSet = 0x100000,
            EmitterSizeSet = 0x10000000,
            Unk20000000 = 0x20000000,
            LocalScaleSet = 0x40000000,
        };

        void* vtable;
        u32 status;
        u32 _8; // something to do with status
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
        nw4r::math::VEC3 velSpecDir;
        nw4r::math::VEC3 velSpecDirAdd;

        nw4r::ut::Color color;
        nw4r::ut::Color registerColors[4];

        nw4r::math::VEC2 defaultScale;
        nw4r::math::VEC2 scale;
        nw4r::math::VEC3 defaultRot;
        nw4r::math::VEC3 rot;
        nw4r::math::VEC3 emitterSize;
        nw4r::math::VEC3 localScale;
};

class Effect {
    public:
        void* vtable;
        char name[0x20];
        u32 creatorId; // must always be zero
        u32 flags; // &1 = has translation, &2 = matrix set, &4 = ??
        nw4r::math::VEC3 scale;
        nw4r::math::VEC3 translate;
        nw4r::math::MTX34 matrix;
        nw4r::ef::HandleBase handle;
        ExEffectParam exParams;
};

} // namespace EGG
