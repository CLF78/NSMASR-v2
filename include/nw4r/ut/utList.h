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

typedef struct {
    u32 count;
    Link node;
} LinkListImpl;

void* List_GetNext(const List* list, const void* object);

} // namespace ut
} // namespace nw4r
