#pragma once

class sStateMethod_c {
    public:
        sStateMethod_c(sStateIdChkIf_c& chkIf, sStateFctIf_c& executor, const sStateIDIf_c& initialState);
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
        virtual void changeStateLocalMethod(const sStateIDIf_c&) = 0;

        sStateIdChkIf_c& chkIf;
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

        sStateFctIf_c& currExecutor;
};
