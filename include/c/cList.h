#pragma once

// Forward declaration
class fBase_c;

class cListNd_c {
    public:
        cListNd_c* prev;
        cListNd_c* next;
        fBase_c* owner;
};

class cListNdExt_c : cListNd_c {
    public:
        u16 _C; // count maybe?
        u16 _E; // offset maybe?
};

class cListMg_c {
    public:
        cListNdExt_c* first;
        cListNd_c* last;
};
