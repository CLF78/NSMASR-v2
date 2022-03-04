#pragma once

#include <kamek.h>

namespace nw4r {
namespace ef {

struct EmitterInheritSetting {
    enum EmitterInheritSettingFlag {
        FLAG_FOLLOW_EMITTER = 1, // unused
        FLAG_INHERIT_ROTATE = 2
    };

    s16 speed;
    u8 scale;
    u8 alpha;
    u8 color;
    u8 renderPrio;
    u8 type; // 0 = particle, 1 = emitter
    u8 flag;
    u8 alphaFuncPri; // &1 = Use primary alpha, &2 = Use secondary alpha, &4 = Use alpha swing and Modifier
    u8 alphaFuncSec; // same as above
};

} // namespace ef
} // namespace nw4r
