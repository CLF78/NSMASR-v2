class cTreeNd_c {
    public:
        cTreeNd_c* parent;
        cTreeNd_c* child;
        cTreeNd_c* prev;
        cTreeNd_c* next;
        void* owner;
};

class cTreeMg_c {
    public:
        cTreeNd_c* root;
};
