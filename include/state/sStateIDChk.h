#pragma once
#include <state/sStateIDIf.h>
#include <state/sStateIDChkIf.h>

class sStateIDChk_c : public sStateIDChkIf_c {
    public:
        virtual ~sStateIDChk_c();
        virtual bool isNormalID(const sStateIDIf_c&) const;
};
