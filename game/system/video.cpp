#include <kamek.h>

// Progressive copy filter patch (from mkw-sp)
kmCallDefAsm(0x802BB068) {
	// Original instruction
	cntlzw r0, r3

	// Check that the mode is progressive
	lwz r5, 0x14(r5)
	cmpwi r5, 0
	bnelr+

	// Disable the copy filter
	li r0, 0
	blr
}
