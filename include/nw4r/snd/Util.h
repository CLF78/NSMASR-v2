#pragma once
#include <kamek.h>

namespace nw4r {
namespace snd {
namespace detail {

class Util {
    public:
        struct DataRef {
            u8 refType; // 0 = address, 1 = offset
            u8 dataType;
            u16 reserved;
            u32 value;
        };

        template<typename T>
        struct Table {
            u32 count;
            T items[1]; // actually multiple
        };
};

} // namespace detail
} // namespace snd
} // namespace nw4r
