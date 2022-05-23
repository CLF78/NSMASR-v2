#pragma once
#include <kamek.h>
#include <m/m3d/banm.h>

namespace m3d {

// Values unknown, these are just guesses
enum playMode_e {
    Play = 1,
    PlayReverse = 2,
    Unk4 = 4,
};

class fanm_c : public banm_c {
    public:
        float numFrames;
        float startFrame;
        float currentFrame;
        u8 playMode;
        // 3 bytes padding
};

} // namespace m3d
