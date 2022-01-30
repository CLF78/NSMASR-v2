#include <kamek.h>
#include <rvl/os/OS.h>

// Hijack the end of dAcPy_c's constructor
kmBranchDefCpp(0x801447D4, NULL, void *, void *obj) {
    OSReport("dAcPy_c constructed at %p!\n", obj);
    return obj;
}
