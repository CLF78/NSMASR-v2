// I didn't know where to put this
#include <kamek.h>

// Only used for Hint Movies
struct MovieType {
    enum Value {
        SuperSkills,
        Infinite1UP,
        StarCoins,
        SecretExit,
    };
};

struct ScreenType {
    enum Value {
        Normal,
        SuperGuide,
        Title,
        TitleReplay,
        HintMovie,
    };
};

struct StartGameInfo {
    u32 replayDuration;     // 0x00 (in frames, max value 0x3840 aka 4 minutes)
    u8 movieType;           // 0x04
    u8 entrance;            // 0x05
    u8 area;                // 0x06
    bool isReplay;          // 0x07
    u32 screenType;         // 0x08 (alters HUD)
    u8 world1;              // 0x0C
    u8 level1;              // 0x0D
    u8 world2;              // 0x0E (usually copied from the other field)
    u8 level2;              // 0x0F (usually copied from the other field)
};
