#include <kamek.h>
#include <fBase/dBase/dScene/dScene.h>

class dScWMap_c : public dScene_c {
    public:
        static u32 assembleSettings(u32 worldNum, u32 sceneNo, u32 unk);

        static u8 m_PrevWorldNo;
};
