#pragma once
#include <kamek.h>
#include <nw4r/lyt/Types.h>
#include <nw4r/math/types.h>
#include <nw4r/ut/utList.h>

namespace nw4r {
namespace lyt {
namespace detail {

class PaneBase {
    public:
        void* vtable;
        ut::Link link;
};

} // namespace detail

namespace res {
struct ExtUserDataList;
} // namespace res

class Material;

class Pane : public detail::PaneBase {
    public:
        Pane* parent;
        ut::LinkListImpl childList;
        ut::LinkListImpl animList;

        Material* material;

        math::VEC3 translate;
        math::VEC3 rotate;
        math::VEC2 scale;
        Size size;

        math::MTX34 mtx;
        math::MTX34 globalMtx;

        const res::ExtUserDataList* extUserDataList;

        u8 alpha;
        u8 globalAlpha;
        u8 basePosition;
        u8 flag;

        char name[17];
        char userData[9];
        bool userAllocated;
        // 1 byte padding
};

} // namespace lyt
} // namespace nw4r
