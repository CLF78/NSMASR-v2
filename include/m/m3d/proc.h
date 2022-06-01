#pragma once
#include <m/m3d/scnLeaf.h>

namespace m3d {

class proc_c : public scnLeaf_c {
    public:
        virtual ~proc_c();
        virtual LeafType::Value getType() const;
        virtual void drawOpa() = 0;
        virtual void drawXlu() = 0;
};

} // namespace m3d
