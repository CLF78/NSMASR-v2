#include <kamek.h>
#include <daPyMng.h>

// Extern for ASM call
extern "C" void SetPlayerID(dAcPy_c* player);

void SetPlayerID(dAcPy_c* player) {

	// Check if character ID is 4
	if ((player->settings & 0xF) == 4) {

		// Find the first free player ID
		int i;
		for (i = 0; i < 4; i++) {
			if (daPyMng_c::m_playerID[i] == 0)
				break;
		}

		// Set it in the settings
		player->settings &= ~0xF;
		player->settings |= i;

		// Set the create flag to mark it as a Toad
		daPyMng_c::mCreateItem[i] = 8;

		// Set power-up to Mushroom
		daPyMng_c::mKinopioMode = Powerup::Mushroom;
	}
}

// Adjust player id for NPC Toad
kmBranchDefAsm(0x80144428, 0x80144430) {

	// No stack saving needed
	nofralloc

	// Skipped instruction
	stw r4, 0x14FC(r30)

	// Call CPP function
	mr r3, r30
	bl SetPlayerID

	// Original instruction
	mr r3, r28
	blr
}

// Disable DemoControl states
kmWrite16(0x8012CD78, 0x4800);
kmWrite16(0x80130450, 0x4800);

// Prevent NPC Toad from warping with other players
kmWrite16(0x80144CA0, 0x4800);
