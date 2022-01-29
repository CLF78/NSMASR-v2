#pragma once

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

#ifdef __cplusplus
}
#endif
