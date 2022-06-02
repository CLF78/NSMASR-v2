// Source: RVL SDK
#include <kamek.h>
#include <rvl/os/OSThread.h>

#ifdef __cplusplus
extern "C" {
#endif

struct OSMutex {
    OSThreadQueue queue;
    OSThread* thread;
    s32 count;
    OSMutexLink link;
};

void OSLockMutex (OSMutex* mutex);
void OSUnlockMutex (OSMutex* mutex);

#ifdef __cplusplus
}
#endif
