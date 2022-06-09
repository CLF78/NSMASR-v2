#include <rvl/gx/GXEnum.h>

#ifdef __cplusplus
extern "C" {
#endif

void GXClearVtxDesc();
void GXSetVtxDesc(GXAttr::Value attr, GXAttrType::Value type);

void GXSetVtxAttrFmt(u32 vtxfmt, GXAttr::Value attr, GXCompCnt::Value cnt, GXCompType::Value type, u8 frac);

void GXBegin(GXPrimitive::Value type, u32 vtxfmt, u16 numVerts);
void GXEnd();

void GXSetNumTexGens(u8 numTexGens);
void GXSetLineWidth(u8 width, GXTexOffset::Value texOffset);
void GXSetPointSize(u8 width, GXTexOffset::Value texOffset);

#ifdef __cplusplus
}
#endif
