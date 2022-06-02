#include <fBase/dBase/dBase.h>
#include <s/sPhase.h>

class dScene_c : public dBase_c {
    public:
        sPhase_c* initChain;

        static void setNextScene(u16 profileId, ulong settings, bool isCourseOut);
};
