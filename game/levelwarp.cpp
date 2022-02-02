#include <kamek.h>
#include <dCdFile.h>
#include <dInfo.h>
#include <dNext.h>
#include <fBase/dBase/dScene/dScene.h>
#include <fBase/dBase/dScene/dScWMap.h>
#include <profileid.h>
#include <startinfo.h>

// Extern required by asm call
extern "C" {
bool WarpToStage(dNext_c* data, int fromWorld, int fromLevel);
}

bool WarpToStage(dNext_c* data, int fromWorld, int fromLevel) {
	// Since these values are used quite a bit, preload them
	int destWorld = data->entranceData.destWorld;
	int destLevel = data->entranceData.destLevel;

	// Restore original behaviour if we are not in regular gameplay
	if (dInfo_c::m_startGameInfo.screenType != NORMAL)
		return false;

	// Restore original behaviour if destWorld or destLevel are 0
	if (destWorld == 0 || destLevel == 0)
		return false;

	// TODO: Save current level progress

	// Otherwise set world, level, area, screenType and entrance in LevelStartStruct
	// Other fields do not need to be reset as we they are already correct
	LevelStartStruct.world1 = destWorld-1;
	LevelStartStruct.world2 = destWorld-1;
	LevelStartStruct.level1 = destLevel-1;
	LevelStartStruct.level2 = destLevel-1;
	LevelStartStruct.screenType = NORMAL;
	LevelStartStruct.area = data->entranceData.destArea;
	LevelStartStruct.entrance = data->entranceData.destId;

	// Set previous world in order not to reset the map position
	dScWMap_c::m_PrevWorldNo = destWorld-1;

	// Set map node
	dInfo_c::m_instance->exitMapNode = data->entranceData.destMapNode;

	// Set next scene
	dScene_c::setNextScene(ProfileId::RESTART_CRSIN, 0, false);
	return true;
}

kmCallDefAsm(0x800D0250) {
	// Push stack
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)

	// Setup call
	mr r3, r31
	mr r4, r30
	lbz r5, 0x120D(r28)
	bl WarpToStage

	// Begin popping stack (using r12 to preserve r0)
	lwz r12, 0x14(r1)
	addi r1, r1, 0x10

	// If result is false, resume original function execution
	cmpwi r3, 0
	beq original

	// Otherwise return later
	addi r12, r12, 0xEC
	b end

	// Original instruction
	original:
	li r0, 0

	// Restore LR and return
	end:
	mtlr r12
	blr
}
