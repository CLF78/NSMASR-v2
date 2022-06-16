#include <kamek.h>
#include <nw4r/ut/CharStrmReader.h>

#define CONFIG_PATH "/config.ini"

struct LaunchType {
    enum Value {
        Normal,
        ToStage,
        ToMovie,
    };
};

struct LaunchGameMode {
    enum Value {
        Normal,
        FreePlay,
        CoinBattle,
        SuperGuideReplay,
        HintMovieReplay,
        TitleReplay,
    };
};

struct ColliderDisplayFlags {
    enum Value {
        None,
        Hitboxes,
        Colliders,
        Sensors,
        RideableColliders,
    };
};

struct ConfigKey {
    enum KeyId {
        LaunchType,
        SaveNumber,
        PlayerCount,
        PowerUp,
        HasStar,
        World,
        Level,
        Area,
        Entrance,
        GameMode,
        HintMovieType,
        ShowPregame,
        DrawHitboxes,
        DrawColliders,
        DrawSensors,
        DrawRideableColliders,
        MovieId,
    };

    KeyId keyId;
    char* keyName;
};

class dConfigManager_c {
    public:
        dConfigManager_c();

        void loadConfig();
        void parseConfig(nw4r::ut::CharStrmReader* reader, void* bufferEnd);
        void parseConfigLine(char* key, char* param, int paramSize);

        // Generic
        u8 launchType;
        u8 saveNo;
        u8 playerCount;
        u8 powerUp;
        bool star;

        // Levels only
        u8 world;
        u8 level;
        u8 area;
        u8 entrance;
        u8 gameMode;
        u8 hintMovieType;
        bool showPregame;
        u8 collisionDebugFlags;

        // Movie only
        u8 movieId;

        // Static instance
        static dConfigManager_c* instancePtr;
};
