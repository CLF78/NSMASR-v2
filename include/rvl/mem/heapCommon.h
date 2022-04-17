// Source: RVL SDK
#pragma once
#include <kamek.h>
#include <rvl/mem/list.h>
#include <rvl/os/OSMutex.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    u32 signature;
    MEMLink link;
    MEMList childList;
    void* heapStart;
    void* heapEnd;
    OSMutex mutex;
    u8 reserved[3];
    u8 optFlag;
} MEMiHeapHead;

#ifdef __cplusplus
}
#endif
