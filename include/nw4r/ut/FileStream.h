#pragma once
#include <kamek.h>
#include <nw4r/ut/IOStream.h>

namespace nw4r {
namespace ut {

class FileStream : public IOStream {
    public:
        virtual u32 GetSize() const;
        virtual void Seek(s32 offset, u32 origin);
        virtual void Cancel();
        virtual bool CancelAsync(IOStreamCallback callback, void* arg);
        virtual bool CanSeek() const;
        virtual bool CanCancel() const;
        virtual u32 Tell() const;

        u32 fileSize;
        u32 position;
};

} // namespace ut
} // namespace nw4r
