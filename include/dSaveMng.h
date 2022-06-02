#include <kamek.h>
#include <dMj2dHeader.h>
#include <dMj2dGame.h>

class dSaveMng_c {
    public:
        bool isNowSave; // set to true when accessing NAND
        u8 pad[0x1F];
        dMj2dHeader_c save;

        static dSaveMng_c* m_instance;

        dMj2dGame_c* getSaveGame(s8 slot);
};
