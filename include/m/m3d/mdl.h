#pragma once
#include <m/m3d/calcratio.h>
#include <m/m3d/smdl.h>
#include <m/mHeap/mAllocator.h>
#include <nw4r/g3d/res/resanmchr.h>

namespace m3d {

class mdl_c : public smdl_c {
    public:
        class mdlCallback_c {
            public:
                void* vtable;
                calcRatio_c calcRatio;
                u32 resCount;
                nw4r::g3d::ChrAnmResult* results;
                mdlCallback_c* childCallback;
                mAllocator_c* allocator;
        };

        virtual ~mdl_c();
        virtual void remove();
        virtual void setAnm(m3d::banm_c& anm);
        virtual void play();

        mdlCallback_c callback;
};

} // namespace m3d
