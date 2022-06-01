#pragma once
#include <rvl/gx/GXEnum.h>

#ifdef __cplusplus
extern "C" {
#endif

void GXSetBlendMode(GXBlendMode::Value blendMode, GXBlendFactor::Value srcFactor, GXBlendFactor::Value dstFactor, GXLogicOp::Value logicOp);

#ifdef __cplusplus
}
#endif
