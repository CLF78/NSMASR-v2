#include <kamek.h>
#include <fBase/dBase/dScene/dScene.h>

class dScWMap_c : public dScene_c {
    public:
        enum CourseType_e {
            Unk1 = 1,
            StarCoins = 2,
            Unk10 = 0x10,
            Unk20 = 0x20,
            Cannon = 0x40,
            GreenToadHouse = 0x80,
            RedToadHouse = 0x100,
            YellowToadHouse = 0x200,
        };

        static void SetCourseTypeForce(int world, int level, CourseType_e type);

        static u32 assembleSettings(u32 worldNum, u32 sceneNo, u32 unk);

        static u8 m_PrevWorldNo;
};
