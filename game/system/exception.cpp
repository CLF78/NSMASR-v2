#include <kamek.h>
#include <nw4r/db/exception.h>
#include <rvl/ax/ax.h>
#include <rvl/os/OSContext.h>
#include <rvl/os/OSError.h>

// Strings
extern char dashes;

#ifdef REGION_P1
#define regionString "P1"
#elif defined(REGION_P2)
#define regionString "P2"
#elif defined(REGION_E1)
#define regionString "E1"
#elif defined(REGION_E2)
#define regionString "E2"
#elif defined(REGION_J1)
#define regionString "J1"
#elif defined(REGION_J2)
#define regionString "J2"
#elif defined(REGION_K)
#define regionString "K"
#elif defined(REGION_W)
#define regionString "W"
#elif defined(REGION_C)
#define regionString "C"
#else
#define regionString "UNK"
#endif

// Helper functions
bool IsValidAddr(u32 addr) {
    return ((addr >= 0x80000000 && addr <= 0x817FFFFF) || (addr >= 0x90000000 && addr <= 0x935E0000));
}

const char* getDashes() {
    return &dashes;
}

extern "C" void printStackTrace(u32* sp) {
    for (u32 i = 0; i < 16; i++) {

        // Check if stack address is valid, if not break
        // Print a newline character if the current line isn't finished
        if (!IsValidAddr((u32)sp)) {
            if (i % 4 != 0)
                nw4r::db::Exception_Printf_("\n");
            break;
        }

        // Display the address
        u32 addr = sp[1] - (4 * (i != 0));
        const char* arrow = (i % 4 == 0) ? "" : " -> ";
        const char* endln = (i % 4 == 3) ? "\n" : "";
        nw4r::db::Exception_Printf_("%s%08X%s%s", arrow, addr, endln);

        // Get caller sp
        sp = (u32*)*sp;
    }
}

// Skip the button sequence
kmWrite32(0x802D7528, 0x48000060);

// Filter the content of the exception handler
kmWrite16(0x803DABB8, 0x23);

// Replace initial text
kmBranchDefCpp(0x80234CD0, 0x80234D08, void) {
    nw4r::db::Exception_Printf_("NSMASR Exception Handler [%s]\n", regionString);
    nw4r::db::Exception_Printf_("Please take a picture of the following information\nand send it to CLF78#7878 on Discord. Use the D-pad \n");
    nw4r::db::Exception_Printf_("to scroll through the data.\n");
}

// Replace heading with simple dashes
kmCall(0x80234D1C, getDashes);

// Override main info
kmCallDefCpp(0x80234D38, void, u16 error, const OSContext* context, ulong dsisr, ulong dar) {

    // For DSI and ISI exceptions, use the SRR0 and determine if the address is in the payload
    // For any other exception, fall back to original call
    u32 srr0 = context->srr0;
    if (error == OS_ERROR_DSI)
        nw4r::db::Exception_Printf_("Invalid load/store operation at %08X\n", srr0);
    else if (error == OS_ERROR_ISI) {
        const char* txt;
        if (IsValidAddr(srr0))
            txt = "Invalid branch from";
        else
            txt = "Invalid instruction at";
        nw4r::db::Exception_Printf_("%s %08X\n", txt, srr0);
    } else
        nw4r::db::ShowMainInfo_(error, context, dsisr, dar);
}

// Replace register head
kmCall(0x80234D50, getDashes);
kmCallDefCpp(0x80234D5C, const char*) {
    return "Registers:\n";
}

// Replace register format string
kmCallDefCpp(0x80234D7C, const char*) {
    return " r%d %08X  r%d %08X  r%d %08X\n";
}

// Replace ending register format string
kmCallDefCpp(0x80234DBC, void, const char*, u32 reg1, u32 regVal1, u32 reg2, u32 regVal2) {
    nw4r::db::Exception_Printf_("r%d %08X  r%d %08X\n", reg1, regVal1, reg2, regVal2);
    nw4r::db::Exception_Printf_(&dashes);
}

// Replace stack trace head
kmCallDefCpp(0x80234F0C, const char*) {
    return "Last function calls:\n";
}

// Replace stack trace (wrapper)
kmBranchDefAsm(0x80234F1C, 0x80235058) {
    nofralloc

    // Call C++ function
    mr r3, r28
    bl printStackTrace
    blr
}

// Mute audio on crash
kmCallDefAsm(0x80234888) {
    nofralloc

    // Original instruction
    mr r28, r3

    // Mute audio
    li r3, 0
    b AXSetMasterVolume
}

// Disable scrolling to the sides
kmWrite32(0x802D7680, 0x48000030);

// Hardcode total line count
kmCallDefCpp(0x802D759C, u32) {
    return 9;
}

// Skip the initial auto-scroll
kmWrite8(0x802D75A7, 0x24);
