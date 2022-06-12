#include <kamek.h>
#include <dMj2dHeader.h>
#include <dMj2dGame.h>

class dSaveMng_c {
    public:
        bool isNowSave; // set to true when accessing NAND
        dMj2dHeader_c save __attribute__ ((aligned (0x20))); // alignment required due to NAND r/w

        static dSaveMng_c* m_instance;

        dMj2dGame_c* getSaveGame(s8 slot);
        void initLoadGame(s8 slot);
};
