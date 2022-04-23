#pragma once
#include <kamek.h>

// Class name currently unknown!
class SndPlayer {
    public:
        void startSound(ulong soundId, VEC2* position, ulong settings); // official name

        static SndPlayer* instance;
};
