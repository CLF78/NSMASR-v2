#pragma once
#include <kamek.h>

class cListNd_c {
    public:
        cListNd_c* prev;
        cListNd_c* next;
        void* owner;
};

// Unofficial name
class cListNdExt_c : public cListNd_c {
    public:
        u16 _C; // count maybe?
        u16 _E; // offset maybe?
};

class cListMg_c {
    public:
        cListNd_c* first;
        cListNd_c* last;
};
