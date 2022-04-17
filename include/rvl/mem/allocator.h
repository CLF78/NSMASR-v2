// Source: RVL SDK
#pragma once
#include <kamek.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MEMAllocator MEMAllocator;
typedef void* (*MEMFuncAllocatorAlloc)(MEMAllocator* pAllocator, u32 size);
typedef void (*MEMFuncAllocatorFree)(MEMAllocator* pAllocator, void* memBlock);

typedef struct {
    MEMFuncAllocatorAlloc alloc;
    MEMFuncAllocatorFree free;
} MEMAllocatorFunc;

struct MEMAllocator {
    MEMAllocatorFunc* funcs;
    void* heap;
    u32 param1;
    u32 param2;
};

#ifdef __cplusplus
}
#endif
