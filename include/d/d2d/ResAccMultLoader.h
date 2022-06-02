#include <d/d2d/ResAccMult.h>
#include <d/dDvd/Loader.h>

namespace d2d {

class ResAccMultLoader_c : public ResAccMult_c {
    public:
        void* resource;
        dDvd::loader_c dvdLoader;
};

} // namespace d2d
