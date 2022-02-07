#pragma once

#include <kamek.h>

class dRes_c {
    public:
        void* getRes(const char* arcName, const char* subfileName);
        void* getRes(const char* arcName, const char* subfileName, u32* length);
};
