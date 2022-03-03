#pragma once

#include <m/m3d/banm.h>
#include <m/m3d/scnLeaf.h>

namespace m3d {

class bmdl_c : public scnLeaf_c {
    public:
        banm_c* anim;
};

} // namespace m3d
