#include <kamek.h>

class dSwitchFlagMng_c {
    public:
        u64 flags;
        float liquidInitialHeights[64];
        float liquidCurrentHeights[64]; // difference with initial height
        s8 liquidMovingDirections[64]; // -1 = down, 0 = stopped, 1 = up
        u64 liquidEventMaskMaybe[64]; // ??
        bool isLiquidMovingMaybe[64]; // ??
        u32 ticksRemaining[64];
        u8 actionFlag[64]; // &1 = inactive, &2 = permanent
        u32 noMusicInterruption[64]; // 0 = plays switch music, 1 = doesn't play it
        s8 playerId; // player who triggered the event, -1 if none, 0-3 otherwise
        // 7 bytes padding

        // Unofficial name
        void set(u32 eventId, int timer, bool activateEvent, bool resetEvent, bool isTimed, bool musicInterruption);

        static dSwitchFlagMng_c* m_instance;
};
