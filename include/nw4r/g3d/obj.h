// Source: nw4r
#pragma once
#include <rvl/mem/allocator.h>

namespace nw4r {
namespace g3d {

class G3dObj {
    public:
        G3dObj* parent;
        MEMAllocator* heap;
};

} // namespace g3d
} // namespace nw4r
