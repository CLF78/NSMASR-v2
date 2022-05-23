#pragma once

namespace m3d {

class calcRatio_c {
    public:
        void* vtable;
        float indirectMtx[2][3];
        bool updated;
        bool calcDone;
        // 2 bytes padding
};

} // namespace m3d
