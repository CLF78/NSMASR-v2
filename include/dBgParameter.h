#include <kamek.h>
#include <egg/core/eggFrmHeap.h>

class dBgParameter_c {
    public:
        void* vtable;
        u16* tileBuffers[3][4];

        float _34;
        float screenLeft;
        float screenTop;
        VEC2 screenSize;
        VEC2 screenCentre;
        VEC2 screenCentre2; // calculated by BgGm

        float _58;
        float _5C;
        float _60;
        float _64;
        float _68;
        float _6C;
        float _70;
        float _74;

        float xOffset;
        float yOffset;

        u8 lastDirectionX;
        u8 lastDirectionY;
        // 2 bytes padding

        u32 pSwitchState;
        u32 pSwitchTimers[3];
        EGG::FrmHeap* bgHeap;

        static dBgParameter_c* ms_Instance_p;
};
