#include <m/m3d/banm.h>
#include <m/m3d/scnLeaf.h>

namespace m3d {

class bmdl_c : public scnLeaf_c {
    public:
        virtual ~bmdl_c();
        virtual LeafType::Value getType() const;
        virtual void remove();
        virtual void setAnm(banm_c& anm);
        virtual void play();

        banm_c* anim;
};

} // namespace m3d
