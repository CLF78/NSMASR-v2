#pragma once
#include <kamek.h>

class dEn_c;

// This class is used to make an actor's scale go back and forth when hit
// Example: hitting Urchins with a Fire Flower
class Boyon {
    public:
        VEC3 size;
        float multiplier;
        float multiplierStep; // step is added/subtracted every 4 frames
        u32 duration;
        dEn_c* parent;
};
