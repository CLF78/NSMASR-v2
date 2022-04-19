#pragma once
#include <kamek.h>
#include <egg/core/eggFrmHeap.h>
#include <fBase/fManager.h>

class fBase_c {
    public:
        enum MAIN_STATE_e {
            STATE_NOT_READY,
            STATE_DESTROY,
            STATE_READY,
        };

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
        // vtable 0x60

        fBase_c();

        virtual int create();
        virtual int preCreate();
        virtual void postCreate(MAIN_STATE_e status);

        virtual int doDelete();
        virtual int preDelete();
        virtual void postDelete(MAIN_STATE_e status);

        virtual int execute();
        virtual int preExecute();
        virtual void postExecute(MAIN_STATE_e status);

        virtual int draw();
        virtual int preDraw();
        virtual void postDraw(MAIN_STATE_e status);

        virtual void deleteReady();

        virtual bool entryFrmHeap(int size, EGG::FrmHeap* heap);
        virtual bool entryFrmHeapNonAdjust(int size, EGG::FrmHeap* heap);
        virtual bool createHeap();

        virtual ~fBase_c();

        void deleteRequest();

        static void* operator new(size_t size);
        static void operator delete(void* ptr);
};
