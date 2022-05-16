#pragma once
#include <state/sStateMethod.h>

class sStateMethodUsr_FI_c : public sStateMethod_c {
    public:
        sStateMethodUsr_FI_c(sStateIdChkIf_c& chkIf, sStateFctIf_c& executor, const sStateIDIf_c& initialState);
        virtual ~sStateMethodUsr_FI_c();

        virtual int initializeStateLocalMethod();
        virtual void executeStateLocalMethod();
        virtual void finalizeStateLocalMethod();
        virtual void changeStateLocalMethod(const sStateIDIf_c&);
};
