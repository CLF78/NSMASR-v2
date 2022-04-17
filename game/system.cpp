#include <kamek.h>

// Allocation - Disable heap adjust
kmWrite32(0x800E532C, 0x48000094);

// Exception Handler - Display by default
kmWrite32(0x80234AE0, 38800000);

// Exception Handler - Replace message
kmCallDefCpp(0x80234CD8, char*, void) {
	return "Mamma mia, the game has crashed!\nPlease take a picture of the info below and send it to CLF78.\nYou can scroll through this report using the D-Pad.\n";
}
