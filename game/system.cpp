#include <kamek.h>

// Prevent fixing heaps
kmWrite32(0x800E532C, 0x48000094);

// Show the exception handler by default
kmWrite32(0x80234AE0, 38800000);

// Replace the exception handler message
kmCallDefCpp(0x80234CD8, char*, void) {
	return "Mamma mia! The game has crashed.\nPlease take a picture of the info below\nand send it to CLF78. You can scroll through\nthis report using the D-Pad.\n";
}
