#include <kamek.h>
#include <c/cList.h>
#include <c/cTree.h>

class fManagerUnused {
    public:
        s16 _0;
        s16 _2;
        u32* _4;
        u8 _8[6];
        s16 _E;
        void* vtable;
};

class fManager_c {
    public:
        cTreeNd_c connect;
        cListNdExt_c execute;
        cListNdExt_c draw;
        cListNd_c search;
        fManagerUnused* unused;
        cListMg_c unused2;
};
