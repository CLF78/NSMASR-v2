#pragma once
#include <kamek.h>
#include <egg/core/eggHeap.h>
#include <m/mDvd/Command.h>

namespace mDvd {

class toMainRam_c : public command_c {
    public:
        u8 _9;
        u8 compressionType;
        // 1 byte padding

        int entryNum;
        void* buffer;
        u32 size;
        u32 _18;
        EGG::Heap* heap;
};

} // namespace mDvd
