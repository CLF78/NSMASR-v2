#pragma once
#include <sStateIDIf.h>

class sStateIDChkIf_c {
    public:
        virtual ~sStateIDChkIf_c();
        virtual bool isNormalID(const sStateIDIf_c&) const = 0;
};
