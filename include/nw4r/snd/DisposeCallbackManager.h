#include <nw4r/ut/utList.h>

namespace nw4r {
namespace snd {
namespace detail {

class DisposeCallback {
    public:
        ut::Link disposeLink;
        void* vtable;
};

} // namespace detail
} // namespace snd
} // namespace nw4r
