#pragma once
#include <kamek.h>

class dEn_c;

class FumiCheckCallback {
    public:
        void* vtable;
};

// haven't understood what this does yet...
class dEnFumiCheck_c {
    public:
        void* vtable;
        u32 _4;
        FumiCheckCallback* callback;
        dEn_c* parent;
};

/* Values of field 4:
0 = Normal
1 = Micro Goomba, Paratroopa
2 = Giant/Mega Goomba
3 = Chainlink Koopa
4 = Item Bubble
5 = Koopalings
6 = Iggy Castle Boss
7 = Scaredy Rat
8 = Spiny
*/
