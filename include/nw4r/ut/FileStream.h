#pragma once
#include <kamek.h>
#include <nw4r/ut/IOStream.h>

namespace nw4r {
namespace ut {

class FileStream : public IOStream {
    public:
        u32 fileSize;
        u32 position;
};

} // namespace ut
} // namespace nw4r
