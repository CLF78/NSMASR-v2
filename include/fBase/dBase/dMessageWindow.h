#pragma once
#include <kamek.h>
#include <fBase/dBase/dBase.h>
#include <nw4r/lyt/Pane.h>
#include <state/sStateMgr.h>
#include <LytBase.h>

class dMessageWindow_c : public dBase_c {
    public:
        sFStateMgr<dMessageWindow_c, sStateMethodUsr_FI_c> stateMgr;

        LytBase_c lytBase;

        nw4r::lyt::Pane* rootPane;
        nw4r::lyt::Pane* T_messages[2];
        nw4r::lyt::Pane* N_proportion;

        bool filesLoaded;
        u8 _255;
        u8 _256;
        u8 _257;
        u8 _258;
        // 3 bytes padding

        u32 msgIdIndex;
};
