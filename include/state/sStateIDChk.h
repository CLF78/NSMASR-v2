#include <state/sStateID.h>

// Interface class
class sStateIDChkIf_c {
    public:
        virtual ~sStateIDChkIf_c();
        virtual bool isNormalID(const sStateIDIf_c& state) const = 0;
};

// Actual class
class sStateIDChk_c : public sStateIDChkIf_c {
    public:
        virtual ~sStateIDChk_c();
        virtual bool isNormalID(const sStateIDIf_c& state) const;
};
