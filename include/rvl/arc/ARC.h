#include <kamek.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void* archiveStartAddr;
    void* fstStart;
    void* fileStart;
    u32 entryNum;
    char* fstStringStart;
    u32 fstLength;
    u32 currDir;
} ARCHandle;

#ifdef __cplusplus
}
#endif
