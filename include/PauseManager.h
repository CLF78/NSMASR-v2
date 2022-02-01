#pragma once

#include <kamek.h>

class PauseManager_c {
    public:
        void* vtable; // Will be removed if necessary

        u32 ptmfIndex;
        u32 selection;  // 0 for Continue, 1 for Quit
        u32 playerNum;  // Player who pressed pause

        u32 _10; // Never read, only stored as 0 once?
        u32 cancelMenuSelection; // 0 for Cancel, 1 for OK

        u8 flags; // &1 = in pause menu, &2 = pausing disabled, &4 = ??
        bool buttonAnimPlaying;
        bool exitingMenu;
        bool willDisplay;
        bool _1C; // stuff with otasukeInfo i think
        bool disablePause; // use this to disable pausing at will, since dScStage_c turns off flag 2 every frame
        // 2 bytes padding
};
