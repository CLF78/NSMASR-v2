#pragma once
#include <m/m3d/banm.h>
#include <m/m3d/fanm.h>

namespace m3d {

class anmTexPat_c : public banm_c {
    public:
        class child_c : public fanm_c {
        };

        child_c* children;
};

} // namespace m3d
