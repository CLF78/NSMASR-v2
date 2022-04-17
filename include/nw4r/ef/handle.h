// Source: nw4r
#pragma once
#include <kamek.h>
#include <nw4r/ef/linkedobject.h>

namespace nw4r {
namespace ef {

class HandleBase {
    public:
        u32 objectID;
        LinkedObject* object;
};

} // namespace ef
} // namespace nw4r
