#include <kamek.h>
#include <fBase/dBase/dBaseActor/dActor/dActor.h>

class dPlayerCountEvent_c : public dActor_c {
    public:
        virtual int create();
        virtual int execute();

        u8 events[4];
        u8 usage;
        bool isDeactivate;

        static dPlayerCountEvent_c* build();
};
