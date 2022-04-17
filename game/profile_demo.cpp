#include <fBase/profile.h>
#include <fBase/profileid.h>

#error "This file is only provided as an example of how to use custom profiles, do not use in your projects!"

extern fBase_c* goombaFunc();
extern const char* goombaFiles;
const SpriteData goombaData = {ProfileId::GoombaTest, 8, -16, 0, 8, 8, 8, 0, 0, 0, 0, 0};
Profile customGoombaProfile = Profile(&goombaFunc, SpriteId::GoombaTest, &goombaData, 0x33, 0x31, 0x12, "EN_KURIBO_TEST", &goombaFiles);

extern fBase_c* blockFunc();
const SpriteData blockData = {ProfileId::BlockTest, 8, -16, 8, -8, 16, 16, 0, 0, 0, 0, 8};
Profile customBlockProfile = Profile(&blockFunc, SpriteId::BlockTest, &blockData, 0x200, 0x20E, 2, "EN_OBJ_HATENA_BLOCK_TEST");
