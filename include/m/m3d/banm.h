#pragma once

#include <nw4r/g3d/anmobj.h>
#include <egg/eggFrmHeap.h>
#include <m/mAllocator.h>

namespace m3d {

class banm_c {
    public:
        void* vtable;
        nw4r::g3d::AnmObj* anmObj;
        EGG::FrmHeap* heap;
        mAllocator_c allocator;
};

} // namespace m3d
