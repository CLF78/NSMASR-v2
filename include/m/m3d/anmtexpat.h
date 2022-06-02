#include <kamek.h>
#include <m/m3d/banm.h>
#include <m/m3d/bmdl.h>
#include <m/m3d/fanm.h>
#include <m/mHeap/mAllocator.h>
#include <nw4r/g3d/res/resanmpat.h>
#include <nw4r/g3d/res/resmdl.h>

namespace m3d {

class anmTexPat_c : public banm_c {
    public:
        class child_c : public fanm_c {
            virtual ~child_c();
            virtual AnmType::Value getType() const;
        };

        anmTexPat_c();
        virtual ~anmTexPat_c();
        virtual AnmType::Value getType() const;
        virtual void remove();
        virtual void play();

        child_c* children;

        bool create(nw4r::g3d::ResMdl model, nw4r::g3d::ResAnmTexPat resPat, mAllocator_c* allocator, size_t* size, long maxChildren);

        void setAnm(bmdl_c& model, nw4r::g3d::ResAnmTexPat resPat, long childIdx, playMode_e playMode);
        void setRate(float rate, long childIdx);
        void setFrame(float frame, long childIdx);
};

} // namespace m3d
