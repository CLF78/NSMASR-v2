#pragma once
#include <kamek.h>

// Interface class
class sStateIDIf_c {
    public:
        sStateIDIf_c(const char* name);
        virtual ~sStateIDIf_c() = 0;

        virtual bool isNull() const = 0;
        virtual bool isEqual(const sStateIDIf_c& state) const = 0;

        virtual bool operator==(const sStateIDIf_c& state) const = 0;
        virtual bool operator!=(const sStateIDIf_c& state) const = 0;

        virtual bool isSameName(const char* name) const = 0;

        virtual const char* name() const = 0;
        virtual u32 number() const = 0;

        char* name;
        u32 id;
};

// Actual base class
class sStateID_c : public sStateIDIf_c {
    public:
        sStateID_c(const char* name);
        virtual ~sStateID_c();

        virtual bool isNull() const;
        virtual bool isEqual(const sStateIDIf_c& state) const;

        virtual bool operator==(const sStateIDIf_c& state) const;
        virtual bool operator!=(const sStateIDIf_c& state) const;

        virtual bool isSameName(const char* name) const;

        virtual const char* name() const;
        virtual u32 number() const;

        static sStateID_c NoState;
};

// Inherited class
template <class TOwner>
class sFStateID_c<TOwner> : public sStateID_c {
    public:
        typedef void (TOwner::*funcPtr)();

        funcPtr begin;
        funcPtr execute;
        funcPtr end;

        virtual ~sFStateID_c<TOwner>();

        virtual bool isSameName(const char* name) const;

        virtual void initializeState(TOwner& owner) const;
        virtual void executeState(TOwner& owner) const;
        virtual void finalizeState(TOwner& owner) const;
};

// Inherited class
template <class TOwner>
class sFStateVirtualID_c<TOwner> : public sFStateID_c<TOwner> {
    public:
        virtual ~sFStateVirtualID_c<TOwner>();

        virtual bool isSameName(const char* name) const;

        virtual void initializeState(TOwner& owner) const;
        virtual void executeState(TOwner& owner) const;
        virtual void finalizeState(TOwner& owner) const;

        sStateIDIf_c& superID() const;

        sStateIDIf_c& super;
};
