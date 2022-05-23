#pragma once
#include <m/m3d/banm.h>
#include <m/m3d/fanm.h>

namespace m3d {

class anmChr_c : public fanm_c {
    public:
        virtual ~anmChr_c();
        virtual AnmType::Value getType() const;
};

} // namespace m3d
