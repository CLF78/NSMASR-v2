#pragma once
#include <kamek.h>

class sStateIDIf_c {
    public:
        sStateIDIf_c(const char* name);
        virtual ~sStateIDIf_c();

        virtual bool isNull() const;
        virtual bool isEqual(const sStateIDIf_c&) const;

        virtual bool operator==(const sStateIDIf_c&) const;
        virtual bool operator!=(const sStateIDIf_c&) const;

        virtual bool isSameName(const char* name) const;

        virtual const char* name() const;
        virtual u32 number() const;

        char* name;
        u32 number;

        static sStateIDIf_c NoState;
};
