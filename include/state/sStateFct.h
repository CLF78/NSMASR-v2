#pragma once
#include <state/sState.h>
#include <state/sStateID.h>

// Interface class
class sStateFctIf_c {
    public:
        virtual ~sStateFctIf_c();
        virtual sStateIf_c* build(const sStateIDIf_c& state) = 0;
        virtual void dispose(sStateIf_c*& state) = 0;
};

// Actual class
template <class TOwner>
class sFStateFct_c : public sStateFctIf_c {
    public:
        virtual ~sFStateFct_c();

        virtual sFState_c<TOwner>* build(const sStateIDIf_c& state);
        virtual void dispose(sStateIf_c*& state);

        sFState_c<TOwner> executor;
};
