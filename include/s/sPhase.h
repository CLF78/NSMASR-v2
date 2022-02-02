#pragma once

#include <kamek.h>

typedef bool (*PhaseFunc)(void*);

class sPhase_c {
    public:
        PhaseFunc* functions;
        u16 count;
        u16 current;
};
