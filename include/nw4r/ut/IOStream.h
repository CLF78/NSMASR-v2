#pragma once
#include <kamek.h>

namespace nw4r {
namespace ut {

class IOStream {
    public:
        typedef void (*IOStreamCallback)(s32 result, IOStream* stream, void* arg);

        virtual ~IOStream();
        virtual void Close();
        virtual s32 Read(void* buf, u32 length);
        virtual bool ReadAsync(void* buf, u32 length, IOStreamCallback callback, void* arg);
        virtual s32 Write(const void* buf, u32 length);
        virtual bool WriteAsync(const void* buf, u32 length, IOStreamCallback callback, void* arg);
        virtual bool IsBusy() const;
        virtual bool CanAsync() const;
        virtual bool CanRead() const;
        virtual bool CanWrite() const;
        virtual u32 GetOffsetAlign() const;
        virtual u32 GetSizeAlign() const;
        virtual u32 GetBufferAlign() const;

        bool available;
        s32 asyncResult;
        IOStreamCallback callback;
        void* arg;
};

} // namespace ut
} // namespace nw4r
