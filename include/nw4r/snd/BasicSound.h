#include <kamek.h>

namespace nw4r {
namespace snd {
namespace detail {

struct SoundActorParam {
    f32 volume;
    f32 pitch;
    f32 pan;
};

class BasicSound {
    public:

        class AmbientParamUpdateCallback {
            public:
                void* vtable;
        };

        class AmbientArgUpdateCallback {
            public:
                void* vtable;
        };

        class AmbientArgAllocaterCallback {
            public:
                void* vtable;
        };

        struct AmbientInfo {
            AmbientParamUpdateCallback* paramUpdateCallback;
            AmbientArgUpdateCallback* argUpdateCallback;
            AmbientArgAllocaterCallback* argAllocaterCallback;
            void* arg;
            size_t argSize;
        };

        void SetId(ulong id);
};

} // namespace detail
} // namespace snd
} // namespace nw4r
