#pragma once

namespace mDvd {

class command_c {
    public:
        void* vtable;
        command_c* next;
        bool ready;
};

} // namespace mDvd
