#include <kamek.h>
#include <fBase/fBase.h>
#include <fBase/profileid.h>
#include <fBase/profile.h>
#include <dGameCom.h>
#include <dSwitchFlagMng.h>
#include <PauseManager.h>
#include "sprites/messagespawner.h"

// Externs for ASM calls
extern "C" {
void GetCustomBMG();
void MessageAnimCheck(dMessageWindow_c* self);
}

// Build function
dMessageSpawner_c* dMessageSpawner_c::build() {
    return new dMessageSpawner_c;
}

// Constructor (creates the message window)
dMessageSpawner_c::dMessageSpawner_c() {
    this->box = (dMessageWindow_c*)fBase_c::createChild(ProfileId::MESSAGE_WINDOW, this, 0, 0);
}

// Do not run create until the message window files have loaded
int dMessageSpawner_c::preCreate() {
    return this->box->filesLoaded;
}

// Set up the settings
int dMessageSpawner_c::create() {

    // Set the box's draw order lower to draw it behind other UI elements
    this->box->lytBase.drawOrder = 0;

    // Set up BMG id (and set a dummy entry in the index)
    this->box->customBmgId = this->settings & 0xFFFF;
    this->box->msgIdIndex = 21;

    // Hide the letterbox if necessary
    if (this->settings >> 16 & 1) {
        nw4r::lyt::Pane* window = this->box->rootPane->FindPaneByName("W_message_00");
        window->alpha = 0;
    }

    // Disable the sound if set
    this->box->disableSound = this->settings >> 17 & 1;

    // Check if event is to be activated once
    this->activateOnce = this->settings >> 18 & 1;

    // Check if the sprite is event triggered, and if not display it immediately
    this->eventTriggered = bool(this->eventMask);
    if (!this->eventTriggered) {
        this->box->startAnime = true;
        this->box->display = true;
    }

    return 1;
}

int dMessageSpawner_c::execute() {

    // Dynamically show/hide the box if event triggered
    if (this->eventTriggered) {
        bool eventOn = bool(dSwitchFlagMng_c::m_instance->flags & this->eventMask);

        // If the event is activated and the box isn't already displaying, fade it in!
        if (eventOn && !this->box->display) {
            this->box->startAnime = true;
            this->box->display = true;

        // If the event is deactivated, the box is displaying and the box can be deactivated, fade it out!
        } else if (!eventOn && this->box->display && !this->activateOnce)
            this->box->exitAnime = true; // display will be unset automatically when the animation ends
    }

    // If box is displaying, update its position
    if (this->box->display) {
        VEC2 currPos = {this->pos.x, this->pos.y};
        dGameCom::CalcLayoutPos(&currPos);
        this->box->rootPane->translate.x = currPos.x + 12.0f;
        this->box->rootPane->translate.y = currPos.y - 193.0f;
    }

    return 1;
}

// Profile
const SpriteData messageSpawnerData = {ProfileId::MSG_DISPLAY, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8};
Profile messageSpawnerProfile = Profile(&dMessageSpawner_c::build, SpriteId::MSG_DISPLAY, &messageSpawnerData, ProfileId::MESSAGE_WINDOW-1, ProfileId::MESSAGE_WINDOW-1, 0, "MSG_DISPLAY");

// Patch dMessageWindow to display custom messages
asm void GetCustomBMG() {

    // Check for the custom index we set earlier
    cmpwi r0, 80
    blt+ regularBMG

    // If so, load our custom bmg id and set category to 0
    lhz r6, 0x25A(r31)
    li r28, 0
    blr

    // Else execute original instruction
    regularBMG:
    lwzx r6, r30, r0
    blr
}

// Patch dMessageWindow to stop animating when the game is paused
void MessageAnimCheck(dMessageWindow_c* self) {
    if (!PauseManager_c::m_Pause)
        self->lytBase.AnimePlay();
}

// BMG Hooks
kmCall(0x8078B3EC, GetCustomBMG);
kmCall(0x8078B41C, GetCustomBMG);

// Patch dMessageWindow to optionally disable audio
kmCallDefAsm(0x8078B494) {

    // No stack saving needed
    nofralloc

    // Original instruction
    li r5, 1

    // Branch later if sound is disabled
    mflr r12
    lbz r11, 0x259(r31)
    slwi r11, r11, 2
    add r12, r12, r11
    mtlr r12
    blr
}

// Disable animation hook
kmCallDefAsm(0x8078B200) {
    // No stack saving needed
    nofralloc

    // Call CPP function
    mr r3, r31
    b MessageAnimCheck
}
