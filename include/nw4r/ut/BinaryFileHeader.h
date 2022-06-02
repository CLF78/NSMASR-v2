#include <kamek.h>

namespace nw4r {
namespace ut {

struct BinaryFileHeader {
    u32 signature;
    u16 byteOrder;
    u16 version;
    u32 fileSize;
    u16 headerSize;
    u16 dataBlocks;
};

} // namespace ut
} // namespace nw4r
