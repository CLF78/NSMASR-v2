#pragma once

#include <kamek.h>
#include <egg/eggFrmHeap.h>
#include <f/fManager.h>
#include <profileid.h>

class fBase_c {
    public:
        u32 uniqueId; // unique for every actor
        u32 settings; // nybbles 5 to 12 of spritedata settings
        u16 profileId; // aka actor id

        // The following is for internal usage
        bool created;
        bool deleted;
        bool notDeferred;
        bool deferred;
        u8 groupType; // 0 = none, 1 = scene, 2 = stage
        u8 processType; // &1 = connect, &2 = create, &4 = execute, &8 = delete, &16 = draw
        fManager_c mgr;
        EGG::FrmHeap* heap;

        // Will be removed when no longer necessary
        void* vtable;
};
