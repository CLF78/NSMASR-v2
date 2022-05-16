#pragma once
#include <kamek.h>
#include <state/sStateIDIf.h>

class sStateID_c : public sStateIDIf_c {
    public:
        sStateID_c(const char* name);
        virtual ~sStateID_c();

        virtual bool isNull() const;
        virtual bool isEqual(const sStateIDIf_c&) const;

        virtual bool operator==(const sStateIDIf_c&) const;
        virtual bool operator!=(const sStateIDIf_c&) const;

        virtual bool isSameName(const char* name) const;

        virtual const char* name() const;
        virtual u32 number() const;

        char* name;
        u32 number;
};
