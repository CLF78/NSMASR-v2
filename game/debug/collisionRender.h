#pragma once
#include <m/m3d/proc.h>

class dCollisionRenderProc_c : public m3d::proc_c {
    public:
        dCollisionRenderProc_c();
        virtual void drawOpa();
        virtual void drawXlu();
};
