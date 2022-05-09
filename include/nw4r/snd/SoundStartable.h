#pragma once

namespace nw4r {
namespace snd {

class SoundStartable {
    public:
        void* vtable2; // using 2 due to conflicts in SoundArchivePlayer
};

} // namespace snd
} // namespace nw4r
