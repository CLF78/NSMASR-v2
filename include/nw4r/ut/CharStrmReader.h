#include <kamek.h>

namespace nw4r {
namespace ut {

class CharStrmReader {
    public:
        typedef u16 (CharStrmReader::*ReadNextCharFunc)();

        void* charStrm;
        ReadNextCharFunc readFunc;

        // Set/get stream
        void Set(void* stream) { this->charStrm = stream; }

        void* GetCurrentPos() const { return this->charStrm; }

        // Read a character
        u16 Next() { return (this->*readFunc)(); }

        // Stream operations
        template <typename CharType>
        CharType GetChar(int offset=0) const {
            const CharType* charStrm = (const CharType*)(this->charStrm);
            return *(charStrm + offset);
        }

        template <typename CharType>
        void StepStrm(int step=1) {
            const CharType*& charStrm = (const CharType*&)(this->charStrm);
            charStrm += step;
        }

        // ReadNextCharFunc functions
        u16 ReadNextCharUTF8();
        u16 ReadNextCharUTF16();
        u16 ReadNextCharCP1252();
        u16 ReadNextCharSJIS();
};

} // namespace ut
} // namespace nw4r
