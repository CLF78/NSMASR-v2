#pragma once
#include <nw4r/g3d/scnobj.h>

namespace m3d {

struct LeafType {
    enum Value {
        Smdl = 0,
        Proc = 2,
    };
};

class scnLeaf_c {
    public:
        virtual ~scnLeaf_c();
        virtual LeafType::Value getType() const = 0;
        virtual void remove();
        virtual void entry();

        // vtable 0x0
        nw4r::g3d::ScnObj* scnObj;
};

} // namespace m3d
