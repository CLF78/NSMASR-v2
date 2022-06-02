#include <kamek.h>

namespace nw4r {
namespace g3d {

struct ChrAnmResult {
    u32 flags;
    VEC3 enlargementRatio;
    VEC3 rotationAmount;
    MTX34 rotationPlusMovement;
};

} // namespace g3d
} // namespace nw4r
