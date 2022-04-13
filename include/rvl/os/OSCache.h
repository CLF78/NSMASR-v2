#pragma once

#include <kamek.h>

#ifdef __cplusplus
extern "C" {
#endif

void __flush_cache(void* buffer, int size);

#ifdef __cplusplus
}
#endif
