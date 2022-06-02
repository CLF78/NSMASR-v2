// Source: nw4r
#include <kamek.h>
#include <nw4r/g3d/res/rescommon.h>
#include <rvl/gx/GXEnum.h>

namespace nw4r {
namespace g3d {

struct ResTexData {
    ResBlockHeaderData header;
    u32 revision;
    s32 toResFileData;  // Offset from the start of the structure to ResFileData
    s32 toTexData;      // Offset from the start of the structure to the texture data
    s32 name;           // Offset from the start of the structure to the texture name
    u32 flag;           // 0 = use GXTexFmt, 1 = use GXCITexFmt
    u16 width;
    u16 height;

    union {
        GXTexFmt fmt;
        GXCITexFmt cifmt;
    };

    u32 mipmap_level;   // Number of mipmap levels, 1 if there is no mipmap.
    f32 min_lod;
    f32 max_lod;
    s32 original_path;  // Offset from the start of the structure to the absolute path of the intermediate file that generated this one
    s32 toResUserData;  // Offset from the start of the structure to the user data (0 if none)

    // User data here
    // ALIGN(32)
    // Texture data here
};

class ResTex : public ResCommon<ResTexData> {
};

} // namespace g3d
} // namespace nw4r
