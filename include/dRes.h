#include <kamek.h>

// Actually a subclass of dResMng_c but i'm dumb so i can't do it correctly
class resCallback_c {
    public:
        void* vtable;
};

class dRes_c {
    public:
        void* array; // actually a subclass but i can't be arsed
        u16 count;
        // 2 bytes padding
        resCallback_c* callback;

        void* getRes(const char* arcName, const char* subfileName) const;
        void* getRes(const char* arcName, const char* subfileName, size_t* length) const;
};

class dResMng_c {
    public:
        void* vtable;
        dRes_c res;
        resCallback_c callback;

        static dResMng_c* instance;
};
