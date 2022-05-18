#pragma once
#include <m/m2d/Base.h>
#include <m/m2d/Layout.h>
#include <nw4r/lyt/DrawInfo.h>

namespace d2d {

class ResAccMult_c;

class Multi_c : public m2d::Base_c {
    public:
        m2d::Layout_c layout;
        nw4r::lyt::DrawInfo drawInfo;
        ResAccMult_c* resAccPtr;
        VEC2 pos;
        VEC2 clip;
        VEC2 clipSize;
        bool clippingEnabled;
        // 3 bytes padding
        u32 hasAnims;
        u32 _A8;
};

} // namespace d2d
