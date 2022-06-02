#include <m/m3d/scnLeaf.h>
#include <m/mHeap/mAllocator.h>

namespace m3d {

class proc_c : public scnLeaf_c {
    public:
        proc_c() {};
        virtual ~proc_c() {};
        virtual LeafType::Value getType() const;
        virtual void drawOpa() = 0;
        virtual void drawXlu() = 0;

        void create(mAllocator_c* allocator, ulong* size);
};

} // namespace m3d
