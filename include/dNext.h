#include <kamek.h>
#include <course/NextGoto.h>
#include <dFader.h>

class dNext_c {
    public:
        NextGoto entranceData;
        u32 warpInfo; // 0 = different area, 1 = same area, different zone, 2 = same zone
        bool exitIsScheduled;
        bool switchingAreas;
        bool switchingScene;
        // 1 byte padding
        s16 timer;
        // 2 bytes padding
        dFader_c::fader_type_e fade;
};
