#include <kamek.h>
#include <fBase/dBase/dBaseActor/dActor/dActorMultiState/dEn/daEnKuriboBase/daEnKuriboBase.h>
#include <m/m3d/anmtexpat.h>
#include <nw4r/g3d/res/resanmpat.h>
#include <nw4r/g3d/res/resfile.h>
#include <nw4r/g3d/res/resmdl.h>

const char* customGoombaWalkAnims[] = {"walk2"};

// Externs for ASM call
extern "C" {
	nw4r::g3d::ResAnmTexPat GetWalkAnim(nw4r::g3d::ResFile resFile, const char* originalName, daEnKuriboBase_c* self);
	void GetCustomAnim(m3d::anmTexPat_c* anmTexPat, nw4r::g3d::ResMdl model, nw4r::g3d::ResAnmTexPat, mAllocator_c* allocator, daEnKuriboBase_c* self);
}

nw4r::g3d::ResAnmTexPat GetWalkAnim(nw4r::g3d::ResFile resFile, const char* originalName, daEnKuriboBase_c* self) {

	// Get nybble 7
	int nybble7 = self->settings >> 0x14 & 0xF;

	// Load the correct animation based on it
	const char* anmName = (nybble7) ? customGoombaWalkAnims[nybble7-1] : originalName;

	// Original call
	return resFile.GetResAnmTexPat(anmName);
}

void GetCustomAnim(m3d::anmTexPat_c* anmTexPat, nw4r::g3d::ResMdl model, nw4r::g3d::ResAnmTexPat resPat, mAllocator_c* allocator, daEnKuriboBase_c* self) {

	// Get nybble 7
	int nybble7 = self->settings >> 0x14 & 0xF;

	// If nybble 7 isn't 0, allocate one more child
	anmTexPat->create(model, resPat, allocator, NULL, 1 + (bool)nybble7);

	// Get custom PAT0; if it's null, bail
	nw4r::g3d::ResAnmTexPat customAnim = self->resFile.GetResAnmTexPat("style");
	if (customAnim.mpData == NULL)
		return;

	// Bind the custom animation
	anmTexPat->setAnm(self->mdl, customAnim, 1, m3d::Paused);

	// Set frame and rate
	anmTexPat->setRate(0.0f, 1);
	anmTexPat->setFrame((float)(nybble7-1), 1);
}

// Hook for PAT0 accessor
kmCallDefAsm(0x80031410) {
	mr r5, r30
	b GetWalkAnim
}

// Hook for custom PAT0 injector
kmCallDefAsm(0x80031438) {

	// No stack saving needed
	nofralloc

	// Call CPP function
	mr r7, r30
	b GetCustomAnim
}
