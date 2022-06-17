#include <kamek.h>
#include <fBase/profile.h>
#include <fBase/profileid.h>
#include <daPyMng.h>
#include <dSwitchFlagMng.h>
#include "sprites/playercountevent.h"

dPlayerCountEvent_c* dPlayerCountEvent_c::build() {
    return new dPlayerCountEvent_c;
}

int dPlayerCountEvent_c::create() {
    // Get the settings
    this->events[0] = this->settings >> 0x1A & 0x3F;
    this->events[1] = this->settings >> 0x14 & 0x3F;
    this->events[2] = this->settings >> 0xE & 0x3F;
    this->events[3] = this->settings >> 0x8 & 0x3F;
    this->usage = this->settings >> 1 & 3;
    this->isDeactivate = this->settings & 1;
    return 1;
}

int dPlayerCountEvent_c::execute() {

    // Get player count
    u32 pCount = daPyMng_c::getNumInGame() - 1;

    // Get the corresponding event and check if it's valid
    u8 targetEvent = this->events[pCount];

    // If the triggering event id was activated, activate the target for the corresponding event
    if (this->eventMask == 0 || dSwitchFlagMng_c::m_instance->flags & this->eventMask) {

        if (targetEvent != 0)
            dSwitchFlagMng_c::m_instance->set(targetEvent - 1, 0, !this->isDeactivate, false, false, false);

        // If single use, delete this actor
        if (this->usage == 0)
            this->deleteRequest();
    }

    // else if usage is "Only While Active", deactivate the target event
    else if (targetEvent != 0 && this->usage >= 2)
        dSwitchFlagMng_c::m_instance->set(targetEvent - 1, 0, this->isDeactivate, false, false, false);

    return 1;
}

// Data copied from sprite 33
const SpriteData playerCntEventData = {ProfileId::PCNTSWICH, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2};
Profile playerCntEventProfile = Profile(&dPlayerCountEvent_c::build, SpriteId::PCNTSWICH, &playerCntEventData, ProfileId::PCNTSWICH, ProfileId::PCNTSWICH, 0, "PCNTSWICH");
