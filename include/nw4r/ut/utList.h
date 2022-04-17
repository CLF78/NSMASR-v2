#pragma once
#include <kamek.h>

namespace nw4r {
namespace ut {

typedef struct {
    void* prev;
    void* next;
} Link;

typedef struct {
    void* head;
    void* tail;
    u16 count;
    u16 offset;
} List;

} // namespace ut
} // namespace nw4r
