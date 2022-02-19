#pragma once

#include <kamek.h>
#include <nw4r/g3d/res/resdic.h>
#include <nw4r/g3d/res/rescommon.h>
#include <nw4r/g3d/res/restex.h>

namespace nw4r {
namespace g3d {

struct ResFileHeaderData {
    char signature[4];
    u16 byteOrder;
    u16 version;
    u32 fileSize;
    u16 headerSize;
    u16 dataBlocks;
};

struct ResTopLevelDictData {
    ResBlockHeaderData header; // "root"
    ResDicData topLevel;
    // Second-level dictionary column
    // ...
    // Character string pool accessed from the dictionary
};

struct ResFileData {
    ResFileHeaderData fileHeader;
    ResTopLevelDictData dict;
};

class ResFile : public ResCommon<ResFileData> {
    public:
        ResTex GetResTex(const char* str) const;
};

} // namespace g3d
} // namespace nw4r
