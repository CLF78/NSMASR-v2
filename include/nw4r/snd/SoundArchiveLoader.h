#pragma once
#include <kamek.h>
#include <nw4r/snd/SoundArchive.h>
#include <nw4r/snd/SoundMemoryAllocatable.h>
#include <nw4r/ut/FileStream.h>
#include <rvl/OS/OSMutex.h>

namespace nw4r {
namespace snd {
namespace detail {

class SoundArchiveLoader {
    public:
        OSMutex mutex;
        const SoundArchive& archive;
        u32 streamArea[128];
        ut::FileStream* stream;

        SoundArchiveLoader(const SoundArchive& arc);

        void* LoadFile(ulong fileId, SoundMemoryAllocatable* allocater);
        s32 ReadFile(ulong fileId, void* buffer, s32 size, s32 offset);
};

} // namespace detail
} // namespace snd
} // namespace nw4r
