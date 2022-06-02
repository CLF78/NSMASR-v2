#include <kamek.h>
#include <m/mEf/effect.h>

namespace mEf {

class levelEffect_c : public effect_c {
    public:
        levelEffect_c* prev;
        levelEffect_c* next;
        bool created;
        bool active;
        // 2 bytes padding
        u32 _120;
        u32 _124;
};

} // namespace mEf
