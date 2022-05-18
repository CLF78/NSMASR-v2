#pragma once
#include <kamek.h>
#include <nw4r/ut/utList.h>

namespace m2d {

class Base_c {
    public:
        nw4r::ut::Link link;
        void* vtable;
        u8 drawOrder;
        // 3 bytes padding
};

} // namespace m2d
