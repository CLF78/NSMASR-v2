#include <nw4r/snd/InstancePool.h>
#include <nw4r/snd/MmlParser.h>
#include <nw4r/snd/SeqTrackAllocator.h>

namespace nw4r {
namespace snd {
namespace detail {

class MmlSeqTrackAllocator : public SeqTrackAllocator {
  public:
    MmlParser* parser;
    PoolImpl trackPool;
};

} // namespace detail
} // namespace snd
} // namespace nw4r
