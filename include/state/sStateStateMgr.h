#pragma once
#include <state/sStateFct.h>
#include <state/sStateID.h>
#include <state/sStateMgr.h>

// Interface class missing!

// Actual class
template <TOwner, TStateMethod, TStateMethod2>
class sStateStateMgr_c<TOwner, TStateMethod, TStateMethod2> {
    public:
        virtual ~sStateStateMgr_c<TOwner, TStateMethod, TStateMethod2>();

        // All these functions call the current StateMgr
        virtual void initializeStateMethod();
        virtual void executeStateMethod();
        virtual void finalizeStateMethod();
        virtual void changeStateMethod(const sStateIDIf_c&);
        virtual void refreshStateMethod();

        virtual sStateFctIf_c& getState() const;
        virtual sStateIDIf_c& getNewStateID() const;
        virtual sStateIDIf_c& getStateID() const;
        virtual sStateIDIf_c& getOldStateID() const;

        virtual int initializeStateLocalMethod();
        virtual void executeStateLocalMethod();
        virtual void finalizeStateLocalMethod();
        virtual void changeStateLocalMethod(const sStateIDIf_c& state);

        // New virtuals
        virtual void enableSecondManagerAndSetState(const sStateIDIf_c& state);
        virtual void resetFirstManagerAndEndState();
        virtual bool isSecondManagerCurrentMgr();
        virtual sStateIDIf_c& getFirstManagerCurrentState();

        sStateMgr_c<TOwner, TStateMethod> mgr1;
        sStateMgr_c<TOwner, TStateMethod2> mgr2;
        sStateMgrIf_c& currentMgr;
};
