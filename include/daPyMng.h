#include <kamek.h>
#include <fBase/dBase/dBaseActor/dActor/daPlBase/dAcPy.h>

class daPyMng_c {
    public:
        static dAcPy_c* getPlayer(int idx);
        static u32 getNumInGame();
        static u32 getEntryNum();

        static u32 m_playerID[4];
        static u32 mPlayerEntry[4];
        static u32 mPlayerType[4];
        static u32 mPlayerMode[4];
        static u32 mCreateItem[4];

        static u32 mKinopioMode;
};
