// Source: https://github.com/riidefi/mkw/blob/master/source/egg/core/eggAllocator.hpp
#pragma once
#include <kamek.h>
#include <egg/core/eggHeap.h>
#include <rvl/mem/allocator.h>

namespace EGG {

class Allocator : public MEMAllocator {
    public:
        void* vtable;
        Heap* mHeap;
        s32 mAlign;
};

} // namespace EGG
