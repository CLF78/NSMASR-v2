#pragma once

#include <fBase/dBase/dBaseActor/dBaseActor.h>
#include <dHeapAllocator.h>
#include <m/m3d/smdl.h>

class daUnitRail_c : public dBaseActor_c {
    public:
        dHeapAllocator_c allocator;
        m3d::smdl_c mdl;
        bool insertedSuccessfully;
        // 3 bytes padding
};
