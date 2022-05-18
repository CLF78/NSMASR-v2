#pragma once
#include <state/sStateID.h>

// Interface class
class sStateIf_c {
    public:
        virtual ~sStateIf_c();

        virtual void initialize() = 0;
        virtual void execute() = 0;
        virtual void finalize() = 0;
};

// Actual class
template <class TOwner>
class sFState_c : public sStateIf_c {
    public:
        virtual ~sFState_c();

        virtual void initialize();
        virtual void execute();
        virtual void finalize();

        TOwner* owner;
        sFStateID_c<TOwner>* state;
};
