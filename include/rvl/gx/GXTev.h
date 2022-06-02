#include <kamek.h>
#include <rvl/gx/GXEnum.h>

#ifdef __cplusplus
extern "C" {
#endif

void GXSetTevOp(u32 stageId, GXTevMode::Value tevMode);
void GXSetTevOrder(u32 stageId, GXTexCoordID::Value coord, GXTexMapID::Value map, GXChannelID::Value color);

void GXSetNumTevStages(u8 numStages);

#ifdef __cplusplus
}
#endif
