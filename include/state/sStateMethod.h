#pragma once
#include <state/sStateFct.h>
#include <state/sStateID.h>
#include <state/sStateIDChk.h>

class sStateMethod_c {
    public:
        sStateMethod_c(sStateIDChkIf_c& check, sStateFctIf_c& executor, const sStateIDIf_c& initialState);
        virtual ~sStateMethod_c();

        virtual void initializeStateMethod();
        virtual void executeStateMethod();
        virtual void finalizeStateMethod();
        virtual void changeStateMethod(const sStateIDIf_c&);
        virtual void refreshStateMethod();

        virtual sStateFctIf_c& getState() const;
        virtual sStateIDIf_c& getNewStateID() const;
        virtual sStateIDIf_c& getStateID() const;
        virtual sStateIDIf_c& getOldStateID() const;

        virtual int initializeStateLocalMethod() = 0;
        virtual void executeStateLocalMethod() = 0;
        virtual void finalizeStateLocalMethod() = 0;
        virtual void changeStateLocalMethod(const sStateIDIf_c& state) = 0;

        sStateIDChkIf_c& check;
        sStateFctIf_c& executor;

        bool initializeOrFinalize;
        bool execute;
        bool active;
        bool stateChanged;
        bool refresh;
        // 3 bytes padding

        sStateIDIf_c& nextState;
        sStateIDIf_c& prevState;
        sStateIDIf_c& currState;

        sStateIf_c& currExecutor;
};

class sStateMethodUsr_FI_c : public sStateMethod_c {
    public:
        sStateMethodUsr_FI_c(sStateIDChkIf_c& check, sStateFctIf_c& executor, const sStateIDIf_c& initialState);
        virtual ~sStateMethodUsr_FI_c();

        virtual int initializeStateLocalMethod();
        virtual void executeStateLocalMethod();
        virtual void finalizeStateLocalMethod();
        virtual void changeStateLocalMethod(const sStateIDIf_c& state);
};
