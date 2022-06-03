#include <rvl/gx/GXEnum.h>

#ifdef __cplusplus
extern "C" {
#endif

void GXSetBlendMode(GXBlendMode::Value blendMode, GXBlendFactor::Value srcFactor, GXBlendFactor::Value dstFactor, GXLogicOp::Value logicOp);

void GXSetZMode(bool compareEnable, GXCompare::Value compareFunc, bool updateEnable);
void GXSetZCompLoc(bool beforeTex);

#ifdef __cplusplus
}
#endif
