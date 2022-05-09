#pragma once
#include <kamek.h>
#include <nw4r/snd/SoundArchive.h>
#include <nw4r/ut/FileStream.h>
#include <rvl/OS/OSMutex.h>

namespace nw4r {
namespace snd {

class SoundArchiveLoader {
    public:
        OSMutex mutex;
        const SoundArchive& archive;
        u32 streamArea[128];
        ut::FileStream* stream;

        SoundArchiveLoader(const SoundArchive& arc);
};

} // namespace snd
} // namespace nw4r
