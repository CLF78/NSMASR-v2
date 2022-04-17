// Source: nw4r
#pragma once
#include <kamek.h>

namespace nw4r {
namespace g3d {

struct ResBlockHeaderData {
    char kind[4];
    u32 size;
};

template<class T>
class ResCommon {
    public:
        T* mpData;
};

} // namespace g3d
} // namespace nw4r
