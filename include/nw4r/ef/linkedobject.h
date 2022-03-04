#pragma once

#include <kamek.h>
#include <nw4r/ut/utList.h>

namespace nw4r {
namespace ef {

class LinkedObject {
    public:
        ut::Link link; // Link used for memory management
        u32 objectID; // ID for use as a handle
};

} // namespace ef
} // namespace nw4r
