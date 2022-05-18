#pragma once
#include <kamek.h>
#include <nw4r/math/types.h>
#include <nw4r/ut/Rect.h>

namespace nw4r {
namespace lyt {

class DrawInfo {
    public:
        void* vtable;
        math::MTX34 viewMtx;
        ut::Rect viewRect;
        math::VEC2 locationAdjustScale;
        float globalAlpha;
        u8 flag;
        // 3 bytes padding
};

} // namespace lyt
} // namespace nw4r
