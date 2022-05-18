#pragma once
#include <kamek.h>
#include <egg/core/eggHeap.h>
#include <m/mDvd/ToMainRam.h>

namespace dDvd {

class loader_c {
    public:
        void* vtable;
        u32 size;
        mDvd::toMainRam_c* command;
        EGG::Heap* heap;
        void* buffer;
};

} // namespace mDvd
