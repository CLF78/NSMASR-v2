// Source: nw4r
#include <kamek.h>
#include <nw4r/g3d/obj.h>
#include <nw4r/math/geometry.h>

namespace nw4r {
namespace g3d {

class IScnObjCallback;

class ScnObj : public G3dObj {
    public:
        MTX34 mtxArray[3]; // 0 = local, 1 = world, 2 = view
        nw4r::math::AABB AABB[2]; // 0 = local, 1 = world
        u32 flags;
        u8 priorityDrawOpa;
        u8 priorityDrawXlu;
        // 2 bytes padding
        IScnObjCallback* callback;
        u8 callbackTiming;
        bool callbackDeleteOption;
        u16 callbackExecOpMask;
};

} // namespace g3d
} // namespace nw4r
