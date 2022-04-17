#pragma once
#include <kamek.h>
#include <dMj2dGame.h>

class dMj2dHeader_c {
    public:
        char titleID[4];            // 0x00
        u8 version;                 // 0x04 (set to 14)
        u8 _5;                      // 0x05
        u8 currentFile;             // 0x06
        u8 _7;                      // 0x07
        u16 freemodeFav[10][42];    // 0x08
        u16 coinbtlFav[10][42];     // 0x350
        u16 bitfield;               // 0x698 (world completion of the current save, bits are 1 << world-1)
        u16 _69A;                   // 0x69A
        u32 checksum;               // 0x69C
        dMj2dGame_c saves[3];       // 0x6A0
        dMj2dGame_c quickSaves[3];  // 0x2320
};
