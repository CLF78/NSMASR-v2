#include <nw4r/ut/utList.h>

namespace nw4r {
namespace snd {
namespace detail {

class ExternalSoundPlayer {
    public:
        ut::LinkListImpl soundList;
        int playableCount;
};

} // namespace detail
} // namespace snd
} // namespace nw4r
