#include <kamek.h>

// Make savefiles region-free
kmWrite8(0x800CF893, 0x3C);
