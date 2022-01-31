#pragma once

// Forward declaration
class fBase_c;

class cTreeNd_c {
    public:
        cTreeNd_c* parent;
        cTreeNd_c* child;
        cTreeNd_c* prev;
        cTreeNd_c* next;
        fBase_c* owner;
};

class cTreeMg_c {
    public:
        cTreeNd_c* root;
};
