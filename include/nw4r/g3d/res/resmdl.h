#pragma once
#include <kamek.h>
#include <nw4r/g3d/res/rescommon.h>

namespace nw4r {
namespace g3d {

struct ResMdlInfoData {
    u32 size; // Size of this structure
    s32 toResMdlData; // Offset from the start of the structure to ResMdlData
    u32 scalingRule;
    u32 texMtxMode;
    s32 vertexSize; // From rmdl
    s32 triangleSize; // From rmdl
    s32 originalPath; // From rmdl
    u32 numViewMtx;
    u8 needNrmMtxArray;
    u8 needTexMtxArray;
    u8 isValidVolume;
    u8 envelopeMtxMode; // Calculation method for the normal matrix and texture matrix that makes up an envelope
    s32 toMtxIDToNodeID;
    VEC3 volumeMin; // From rmdl
    VEC3 volumeMax; // From rmdl
};

struct ResMdlData {
    ResBlockHeaderData header;
    u32 revision;

    // Offsets here
    s32 toResFileData;
    s32 toResByteCodeDic;
    s32 toResNodeDic;
    s32 toResVtxPosDic;
    s32 toResVtxNrmDic;
    s32 toResVtxClrDic;
    s32 toResVtxTexCoordDic;
    s32 toResVtxFurVecDic;
    s32 toResVtxFurPosDic;
    s32 toResMatDic;
    s32 toResTevDic;
    s32 toResShpDic;
    s32 toResTexNameToTexPlttInfoDic;
    s32 toResPlttNameToTexPlttInfoDic;
    s32 toResUserData;
    s32 toName;

    ResMdlInfoData info;
    // Model data here
};

class ResMdl : public ResCommon<ResMdlData> {
};

} // namespace g3d
} // namespace nw4r
