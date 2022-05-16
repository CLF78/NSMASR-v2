#include <kamek.h>

// Fix the excessively harsh out of screen check
kmWrite16(0x80939214, 0x4380);
