#pragma once
#include <kamek.h>

namespace nw4r {
namespace ut {

class IOStream {
    public:
        typedef void (*IOStreamCallback)(s32 result, IOStream* stream, void* arg);

        void* vtable;
        bool available;
        s32 asyncResult;
        IOStreamCallback callback;
        void* arg;
};

} // namespace ut
} // namespace nw4r
