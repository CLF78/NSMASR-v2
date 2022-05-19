#pragma once
#include <d/d2d/Multi.h>
#include <d/d2d/ResAccMultLoader.h>

namespace m2d {

class AnmResV2_c;
class AnmGroup_c;

} // namespace m2d

class LytBase_c : public d2d::Multi_c {
    public:
        d2d::ResAccMultLoader_c loader;

        m2d::AnmResV2_c* brlanHandlers;
        m2d::AnmGroup_c* groupHandlers;

        bool* animsEnabled;
        int animCount;
        int groupCount;
        int lastAnim;

        void AnimePlay();
};
