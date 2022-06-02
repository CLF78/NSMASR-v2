#include <egg/video/eggEffect.h>
#include <m/mTypes.h>

namespace mEf {

class effect_c : public EGG::Effect {
};

bool createEffect(const char* name, ulong owner, const mVec3_c* position, const mAng3_c* rotation, const mVec3_c* scale);

} // namespace mEf
