// Source: https://github.com/riidefi/mkw/blob/master/source/egg/core/eggDisposer.hpp
#pragma once
#include <nw4r/ut/utList.h>

namespace EGG {

// Forward declaration
class Heap;

class Disposer {
    public:
        void* vtable;
        Heap* mContainHeap;
        nw4r::ut::Link mLink;
};

} // namespace EGG
