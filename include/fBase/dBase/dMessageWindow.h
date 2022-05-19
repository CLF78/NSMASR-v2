#pragma once
#include <kamek.h>
#include <fBase/dBase/dBase.h>
#include <nw4r/lyt/Pane.h>
#include <state/sStateMethod.h>
#include <state/sStateMgr.h>
#include <LytBase.h>

class dMessageWindow_c : public dBase_c {
    public:
        sFStateMgr_c<dMessageWindow_c, sStateMethodUsr_FI_c> stateMgr;

        LytBase_c lytBase;

        nw4r::lyt::Pane* rootPane;
        nw4r::lyt::Pane* T_messages[2];
        nw4r::lyt::Pane* N_proportion;

        bool filesLoaded;
        bool display;
        bool startAnime;
        bool exitAnime;
        bool isEndWait;

        bool disableSound; // custom field
        u16 customBmgId; // custom field

        u32 msgIdIndex;
};
