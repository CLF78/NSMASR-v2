#include <kamek.h>

struct BgData {
	u16 zoneId;
	u16 xScrollRate;
	u16 yScrollRate;
	s16 yOffset;
	s16 xOffset;
	u16 fileIds[3];
	u16 fixedBgFileId; // custom field
	u16 scale;
	u32 padding;
};
