#pragma once
#include <nw4r/g3d/scnobj.h>

namespace m3d {

class scnLeaf_c {
    public:
        void* vtable;
        nw4r::g3d::ScnObj* scnObj;
};

} // namespace m3d
