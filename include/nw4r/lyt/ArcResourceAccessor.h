#include <nw4r/lyt/ResourceAccessor.h>
#include <nw4r/ut/utList.h>
#include <rvl/arc/ARC.h>

namespace nw4r {
namespace lyt {

class ArcResourceAccessor : public ResourceAccessor {
    public:
        ARCHandle arcHandle;
        void* arcBuf;
        ut::LinkListImpl fontList;
        char resRootDir[128];
};

} // namespace lyt
} // namespace nw4r
