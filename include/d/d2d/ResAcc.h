#include <nw4r/lyt/ArcResourceAccessor.h>

namespace d2d {

class ResAccIf_c {
    public:
        void* vtable;
        nw4r::lyt::ArcResourceAccessor* accessor;
        void* resource;
};

} // namespace d2d
