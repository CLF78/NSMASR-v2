#pragma once
#include <fBase/dBase/dBaseActor/dBaseActor.h>
#include <m/m3d/smdl.h>
#include <dHeapAllocator.h>

class daUnitRail_c : public dBaseActor_c {
    public:
        dHeapAllocator_c allocator;
        m3d::smdl_c mdl;
        bool insertedSuccessfully;
        // 3 bytes padding
};
