#include <m/mEf/levelEffect.h>
#include <nw4r/ef/emitter.h>

namespace mEf {

class levelOneEffect_c : public levelEffect_c {
    public:
        float emissionRate; // ??
        nw4r::ef::EmitterInheritSetting settings;
};

} // namespace mEf
