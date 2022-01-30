#pragma once

#include <kamek.h>
#include <egg/eggDisposer.h>
#include <nw4r/ut/utList.h>
#include <rvl/mem/heapCommon.h>

// Shamelessly copied from https://github.com/riidefi/mkw/blob/master/source/egg/core/eggHeap.hpp

namespace EGG {

class Heap : public Disposer {
    public:
        MEMiHeapHead* mHeapHandle;
        void* mParentBlock;
        Heap* mParentHeap;
        u16 mFlag;
        // 2 bytes padding
        nw4r::ut::Link mLink;
        nw4r::ut::List mChildren;
        const char* mName;
};

} // namespace EGG
