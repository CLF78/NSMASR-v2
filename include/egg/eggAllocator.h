#pragma once

#include <kamek.h>
#include <egg/eggHeap.h>
#include <rvl/mem/allocator.h>

// Shamelessly copied from https://github.com/riidefi/mkw/blob/master/source/egg/core/eggHeap.hpp

namespace EGG {

class Allocator : MEMAllocator {
    public:
        void* vtable;
        Heap* mHeap;
        s32 mAlign;
};

} // namespace EGG
