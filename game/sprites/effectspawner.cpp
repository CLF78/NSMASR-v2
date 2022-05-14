#include <kamek.h>
#include <fBase/profile.h>
#include <fBase/profileid.h>
#include <m/mTypes.h>
#include <m/mEf/effect.h>
#include <nw4r/ef/resource.h>
#include <nw4r/ut/utList.h>
#include <sound/SndPlayer.h>
#include <dAudio.h>
#include <dSwitchFlagMng.h>
#include <PauseManager.h>
#include "sprites/effectspawner.h"

// A nw4r function to help myself stay sane
u16 breffNumEmitter(nw4r::ef::EffectProject* project) {
    u8* ptr = (u8*)project;
    ptr += project->headersize;
    nw4r::ef::resource::NameTable* nametbl = (nw4r::ef::resource::NameTable*)ptr;
    return nametbl->numEntry;
}

// Build function
dEffectSpawner_c* dEffectSpawner_c::build() {
    return new dEffectSpawner_c;
}

int dEffectSpawner_c::create() {

    // Setup eventFlag (nybbles 5-6)
    u8 eventNum = (this->settings >> 24) & 0xFF;
    this->eventFlag = (u64)1 << (eventNum - 1);

    // Setup scale (nybble 7)
    u16 scale = (this->settings >> 20) & 0xF;
    if (scale == 0)
        scale = 4;
    this->scale = float(scale) / 4.0;

    // Setup effect index (nybbles 10-12)
    this->effect = this->settings & 0xFFF;

    // Setup timer and delay (nybble 9)
    this->delay = ((this->settings >> 12) & 0xF) * 60;
    this->timer = this->delay;

    // Setup isGFX (nybble 8 bit 4)
    this->isGFX = (this->settings >> 16) & 1;

    // Setup runOnce
    this->runOnce = (this->delay == 0);
    return 1;
}

int dEffectSpawner_c::execute() {

    // If event is triggered and the game isn't paused, act!
    if ((dSwitchFlagMng_c::m_instance->flags & this->eventFlag) && (!PauseManager_c::m_Pause)) {

        // If the loop delay matches the timer, play the effect
        if (this->timer == this->delay) {

            // Act depending on the type
            if (isGFX) {

                // Setup breff parsing
                nw4r::ef::Resource* res = &nw4r::ef::Resource::mResource;
                u16 effectIdx = this->effect;
                char* effectName = NULL;

                // Parse linked list
                nw4r::ef::EffectProject* currBreff = (nw4r::ef::EffectProject*)nw4r::ut::List_GetNext(&res->mBREFFList, NULL);
                for (int i = 0; i < res->mBREFFList.count; i++) {

                    // Get the number of entries for the current breff
                    u16 numEmitter = breffNumEmitter(currBreff);

                    // If the index fits in this breff, use it
                    if (effectIdx < numEmitter) {

                        // Get emitter and its name
                        nw4r::ef::EmitterResource* breffEntry = nw4r::ef::breffIndexOf(currBreff, effectIdx);
                        effectName = breffEntry->name;
                        break;
                    }

                    // Else go to the next BREFF and subtract the count
                    effectIdx -= numEmitter;
                    currBreff = (nw4r::ef::EffectProject*)nw4r::ut::List_GetNext(&res->mBREFFList, currBreff);
                }

                // If effect was found, spawn it
                if (effectName) {
                    mAng3_c rotation;
                    rotation.x = 0;
                    rotation.y = 0;
                    rotation.z = 0;
                    mVec3_c scale;
                    scale.x = this->scale;
                    scale.y = this->scale;
                    scale.z = this->scale;
                    mVec3_c pos;
                    pos.x = this->pos.x + 8;
                    pos.y = this->pos.y - 8;
                    pos.z = this->pos.z;
                    mEf::createEffect(effectName, 0, &pos, &rotation, &scale);
                }

            } else {

                // Convert stage position to screen position
                VEC2 soundPos;
                dAudio::convertStagePosition(&soundPos, &this->pos);

                // Play the chosen sound
                SndPlayer::instance->startSound(this->effect, &soundPos, 0);
            }

            // If the effect only needs to be played once delete the sprite, else reset the timer
            if (runOnce)
                this->deleteRequest();
            else
                this->timer = 0;
        }

        // Update timer
        this->timer++;
    }

    return 1;
}

// Profile
const SpriteData effectSpawnerData = {ProfileId::FX_CREATE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8};
Profile effectSpawnerProfile = Profile(&dEffectSpawner_c::build, SpriteId::FX_CREATE, &effectSpawnerData, ProfileId::FX_CREATE, ProfileId::FX_CREATE, 0, "FX_CREATE");
