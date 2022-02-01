#pragma once

#include <fBase/dBase/dBase.h>
#include <s/sPhase.h>

class dScene_c : dBase_c {
    public:
        sPhase_c* initChain;

        static setNextScene(u16 profileId, u32 settings, bool isCourseOut);
};
