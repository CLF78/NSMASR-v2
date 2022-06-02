#include <state/sStateFct.h>
#include <state/sStateID.h>
#include <state/sStateMgr.h>

// Interface class missing!

// Actual class
template <class TOwner, class TStateMethod, class TStateMethod2>
class sFStateStateMgr_c {
    public:
        virtual ~sFStateStateMgr_c();

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

        sFStateMgr_c<TOwner, TStateMethod> mgr1;
        sFStateMgr_c<TOwner, TStateMethod2> mgr2;
        sStateMgrIf_c& currentMgr;
};
