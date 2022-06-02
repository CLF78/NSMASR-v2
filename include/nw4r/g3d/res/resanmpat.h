#include <kamek.h>
#include <nw4r/g3d/res/rescommon.h>

namespace nw4r {
namespace g3d {

struct ResAnmTexPatInfoData {
    u16 numFrames;
    u16 numMaterials;
    u16 numTextures;
    u16 numPalettes;
    bool loop;
};

struct ResAnmTexPatData {
    ResBlockHeaderData header;
    u32 revision;

    s32 toFileData; // Offset to the parent ResFileData
    s32 toTexPatDataDic; // Offset of dictionary of data from material name to ResAnmTexPatMatData
    s32 toTexNameArray; // Offset to the texture name list
    s32 toPaletteNameArray; // Offset to the palette name list
    s32 toTexArray; // Offset to the ResTex array
    s32 toPaletteArray; // Offset to the ResPltt array
    s32 toUserData; // Offset from the start of the structure to the user data (0 if there is no user data).
    s32 name;  // Offset to source rtpa file name (excluding extension)
    s32 originalPath; // Offseto to source rtpa file path

    ResAnmTexPatInfoData info;

    // ResTexPatDataDic here
    // ResAnmTexPatMatData here
    // ResAnmTexPatAnmData here
    // ResTex name offset array here
    // ResPltt name offset array here
    // ResTex array here
    // ResPltt array here
    // String pool here
    // UserData here
};

class ResAnmTexPat : public ResCommon<ResAnmTexPatData> {
};

} // namespace g3d
} // namespace nw4r
