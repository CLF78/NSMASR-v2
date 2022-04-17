// Source: RVL SDK
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    enum Value {
        C4 = 0x8,
        C8 = 0x9,
        C14X2 = 0xA,
    };
} GXCITexFmt;

#define ZTF_FLAG 0x10 // Z-texture-format
#define CTF_FLAG 0x20 // copy-texture-format only

typedef struct {
    enum Value {
        I4 = 0x0,
        I8 = 0x1,
        IA4 = 0x2,
        IA8 = 0x3,
        RGB565 = 0x4,
        RGB5A3 = 0x5,
        RGBA8 = 0x6,
        CMPR = 0xE,

        CR4 = 0x0 | CTF_FLAG,
        CRA4 = 0x2 | CTF_FLAG,
        CRA8 = 0x3 | CTF_FLAG,
        CYUVA8 = 0x6 | CTF_FLAG,
        CA8 = 0x7 | CTF_FLAG,
        CR8 = 0x8 | CTF_FLAG,
        CG8 = 0x9 | CTF_FLAG,
        CB8 = 0xA | CTF_FLAG,
        CRG8 = 0xB | CTF_FLAG,
        CGB8 = 0xC | CTF_FLAG,

        Z8 = 0x1 | ZTF_FLAG,
        Z16 = 0x3 | ZTF_FLAG,
        Z24X8 = 0x6 | ZTF_FLAG,

        CZ4 = 0x0 | ZTF_FLAG | CTF_FLAG,
        CZ8M = 0x9 | ZTF_FLAG | CTF_FLAG,
        CZ8L = 0xA | ZTF_FLAG | CTF_FLAG,
        CZ16L = 0xC | ZTF_FLAG | CTF_FLAG,
    };
} GXTexFmt;

#ifdef __cplusplus
}
#endif
