#include <kamek.h>

struct WaterType {
    enum Value {
        Water,
        Lava,
        Poison,
        RoundBubble,
        TallBubble,
        WideBubble,
    };
};

class dWaterEntry_c {
    public:
        float x, y, z;
        float width, height;
        int isInUse;
        u8 type;
        u8 layer;
        // 2 bytes padding
};

class dWaterEntryMng_c {
    public:
        dWaterEntry_c entries[80];
        float currentStrength; // set by the unused water current sprite
};
