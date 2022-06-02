#include <kamek.h>

class sPhase_c {
    public:
        typedef bool (*PhaseFunc)(void*);

        PhaseFunc* functions;
        u16 count;
        u16 current;
};
