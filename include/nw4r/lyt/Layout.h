#pragma once
#include <nw4r/lyt/Types.h>
#include <nw4r/ut/utList.h>

namespace nw4r {
namespace lyt {

class Pane;
class GroupContainer;

class Layout {
    public:
        void* vtable;
        ut::LinkListImpl animTransList;
        Pane* rootPane;
        GroupContainer* groupContainer;
        Size layoutSize;
};

} // namespace lyt
} // namespace nw4r
