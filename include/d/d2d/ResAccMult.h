#include <d/d2d/ResAcc.h>
#include <nw4r/lyt/ArcResourceAccessor.h>

namespace d2d {

class ResAccMult_c : public ResAccIf_c {
    public:
        class InternalAccessor : public nw4r::lyt::ArcResourceAccessor {
        };

        InternalAccessor accessor;
};

} // namespace d2d
