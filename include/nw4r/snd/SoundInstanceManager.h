#pragma once
#include <nw4r/snd/InstancePool.h>
#include <nw4r/ut/utList.h>

namespace nw4r {
namespace snd {
namespace detail {

class SoundInstanceManager {
    public:
        PoolImpl pool;
        ut::LinkListImpl priorityList;
        OSMutex mutex;
};

} // namespace detail
} // namespace snd
} // namespace nw4r
