// Source: nw4r
#include <kamek.h>

namespace nw4r {
namespace g3d {

struct ResDicNodeData {
    u16 ref;
    u16 flag;
    u16 idxLeft;
    u16 idxRight;
    s32 ofsString;
    s32 ofsData;
};

struct ResDicData {
    u32 size;
    u32 numData;
    ResDicNodeData data[1]; // There are numData + 1 pieces of data
};

} // namespace g3d
} // namespace nw4r
