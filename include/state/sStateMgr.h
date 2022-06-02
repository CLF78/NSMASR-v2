#include <state/sStateFct.h>
#include <state/sStateID.h>
#include <state/sStateIDChk.h>

// All function names are unofficial

// Interface class
class sStateMgrIf_c {
    public:
        virtual ~sStateMgrIf_c();

        // All these are calls to the StateMethod class
        virtual void initializeStateMethod() = 0;
        virtual void executeStateMethod() = 0;
        virtual void finalizeStateMethod() = 0;
        virtual void changeStateMethod(const sStateIDIf_c& state) = 0;
        virtual void refreshStateMethod() = 0;

        virtual sStateFctIf_c& getState() const = 0;
        virtual sStateIDIf_c& getNewStateID() const = 0;
        virtual sStateIDIf_c& getStateID() const = 0;
        virtual sStateIDIf_c& getOldStateID() const = 0;

        virtual int initializeStateLocalMethod() = 0;
        virtual void executeStateLocalMethod() = 0;
        virtual void finalizeStateLocalMethod() = 0;
        virtual void changeStateLocalMethod(const sStateIDIf_c& state) = 0;
};

// Actual class
template <class TOwner, class TStateMethod>
class sFStateMgr_c : public sStateMgrIf_c {
    public:
        virtual ~sFStateMgr_c();

        // All these are calls to the statemethod class
        virtual void initializeStateMethod();
        virtual void executeStateMethod();
        virtual void finalizeStateMethod();
        virtual void changeStateMethod(const sStateIDIf_c& state);
        virtual void refreshStateMethod();

        virtual sStateFctIf_c& getState() const;
        virtual sStateIDIf_c& getNewStateID() const;
        virtual sStateIDIf_c& getStateID() const;
        virtual sStateIDIf_c& getOldStateID() const;

        virtual int initializeStateLocalMethod();
        virtual void executeStateLocalMethod();
        virtual void finalizeStateLocalMethod();
        virtual void changeStateLocalMethod(const sStateIDIf_c& state);

        sStateIDChk_c check;
        sFStateFct_c<TOwner> factory;
        TStateMethod stateMethod;
};
