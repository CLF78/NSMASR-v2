#pragma once

namespace nw4r {
namespace snd {

class SoundMemoryAllocatable {
    public:
        virtual ~SoundMemoryAllocatable();
        virtual void* Alloc(size_t size);
};

} // namespace snd
} // namespace nw4r
