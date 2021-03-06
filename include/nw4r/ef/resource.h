// Source: nw4r
#include <kamek.h>
#include <nw4r/ef/emitter.h>
#include <nw4r/ut/utList.h>

namespace nw4r {
namespace ef {

struct EffectProject {
    u32 headersize;
    ut::Link projectlink;
    u16 projectnameLen;
    u16 padding;
    char* projectname;
};

class Resource {
    public:
        ut::List mBREFFList;
        u32 mNumEmitter;
        ut::List mBREFTList;
        u32 mNumTexture;

        static Resource mResource;
};

static EmitterResource* breffIndexOf(EffectProject* project, u16 idx);

namespace resource {

struct NameTable {
    u32 tablesize;
    u16 numEntry;
    u16 padding;
};

} // namespace resource
} // namespace ef
} // namespace nw4r
