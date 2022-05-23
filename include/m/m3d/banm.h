#pragma once
#include <egg/core/eggFrmHeap.h>
#include <m/mHeap/mAllocator.h>
#include <nw4r/g3d/anmobj.h>

namespace m3d {

struct AnmType {
    enum Value {
        AnmChr,
        AnmVis,
        AnmMatClr,
        AnmTexPat,
        AnmTexSrt,
    };
};

class banm_c {
    public:
        virtual ~banm_c();
        virtual AnmType::Value getType() const = 0;
        virtual void remove();
        virtual void play();

        nw4r::g3d::AnmObj* anmObj;
        EGG::FrmHeap* heap;
        mAllocator_c allocator;
};

} // namespace m3d
