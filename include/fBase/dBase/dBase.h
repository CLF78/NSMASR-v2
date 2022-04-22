#pragma once
#include <c/cTree.h>
#include <fBase/fBase.h>

class dBase_c : public fBase_c {
    public:
        cTreeMg firstLinkedNode;
        char* kindString;
        char* nameString;

        dBase_c();

        virtual int preCreate();
        virtual void postCreate(fBase_c::MAIN_STATE_e status);

        virtual int preDelete();
        virtual void postDelete(fBase_c::MAIN_STATE_e status);

        virtual int preExecute();
        virtual void postExecute(fBase_c::MAIN_STATE_e status);

        virtual int preDraw();
        virtual void postDraw(fBase_c::MAIN_STATE_e status);

        virtual ~dBase_c();

        virtual char* getKindString();
};
