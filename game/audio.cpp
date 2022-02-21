#include <kamek.h>

// Patch BRSTM length automatically (original code by Elias)
kmCallDefAsm(0x80269474) {
	// Let me free
	nofralloc

	// Override value
	lis r31, 0x7FFF
	ori r31, r31, 0xFFFF
	blr
}
