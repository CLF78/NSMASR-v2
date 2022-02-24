#include <kamek.h>
#include <dBgGlobal.h>
#include <dRes.h>
#include <fBase/dBase/dScene/dScStage.h>

#ifdef GRASSCPP
#include "tileset/grass.h"
#endif

#ifdef RANDCPP
#include "tileset/rand.h"
#endif

// Extern for ASM call
extern "C" {
void LoadBins();
}

void LoadBins() {

    // Allocate length on the stack
    size_t length;

    // Process each tileset
    for (int slot = 0; slot < 4; slot++) {

        // Get tileset name
        const char* tileName = dBgGlobal_c::instance->getEnvironment(dScStage_c::m_instance->currentArea, slot);

        // If tileset is null, skip
        if (tileName[0] == '\0')
            continue;

        // Get the grass file
        #ifdef GRASSCPP
        GrassBin* grass = (GrassBin*)dResMng_c::instance->res.getRes(tileName, GRASSDATA, &length);

        // If the file was found and is valid, create the class
        if (grass != NULL && length != 0 && grass->version == GRASSSPECVERSION && dGrassBinMng_c::instance == NULL)
            dGrassBinMng_c::build(grass, (length-3) / sizeof(GrassBinEntry), slot);
        #endif

        // Create the random class
        #ifdef RANDCPP
        dRandTileMng_c::build(dScStage_c::m_instance->currentArea);
        #endif
    }
}

// Preload the data files so we can reuse them anytime in the level
kmCallDefAsm(0x801548FC) {

    // Call function
    bl LoadBins

    // Original instruction
    mr r3, r30
}

// Hijack the function end to destroy the data files
kmBranchDefCpp(0x80154E84, NULL, int, void) {
    #ifdef GRASSCPP
    delete dGrassBinMng_c::instance;
    #endif

    #ifdef RANDCPP
    delete dRandTileMng_c::instance;
    #endif

    return 1;
}
