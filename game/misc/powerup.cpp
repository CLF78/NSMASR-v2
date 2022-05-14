#include <kamek.h>

// Disable powerup freeze
kmWrite8(0x800BB481, 0xED);
