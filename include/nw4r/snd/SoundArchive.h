#include <kamek.h>
#include <nw4r/snd/global.h>
#include <nw4r/snd/SoundArchiveFile.h>
#include <nw4r/ut/FileStream.h>

namespace nw4r {
namespace snd {

class SoundArchive {
    public:
        enum SoundType {
            SOUND_TYPE_INVALID,
            SOUND_TYPE_SEQ,
            SOUND_TYPE_STRM,
            SOUND_TYPE_WAVE,
        };

        struct SoundInfo {
            ulong fileId;
            ulong playerId;
            int actorPlayerId;
            int playerPriority;
            int volume;
            int remoteFilter;
            PanMode panMode;
            PanCurve panCurve;
        };

        struct FilePos {
            ulong groupId;
            u32 index;
        };

        struct FileInfo {
            u32 fileSize;
            u32 waveDataFileSize;
            const char* extFilePath;
            u32 filePosCount;
        };

        struct GroupItemInfo {
            ulong fileId;
            u32 offset;
            u32 size;
            u32 waveDataOffset;
            u32 waveDataSize;
        };

        struct GroupInfo {
            u32 itemCount;
            const char* extFilePath;
            u32 offset;
            u32 size;
            u32 waveDataOffset;
            u32 waveDataSize;
        };

        virtual ~SoundArchive();

        bool ReadSoundInfo(ulong soundId, SoundInfo* info) const;

        virtual const void* detail_GetFileAddress(ulong fileId);
        virtual const void* detail_GetWaveDataFileAddress(ulong fileId);
        virtual int detail_GetRequiredStreamBufferSize();
        virtual ut::FileStream* OpenStream(void* buffer, int size, u32 begin, u32 length);
        virtual ut::FileStream* OpenExtStream(void* buffer, int size, const char* extFilePath, u32 begin, u32 length);
        ut::FileStream* detail_OpenFileStream(ulong fileId, void* buffer, int size) const;

        ulong GetGroupCount() const;
        ulong detail_GetFileCount() const;

        ulong GetSoundUserParam(ulong soundId) const;
        SoundType GetSoundType(ulong soundId) const;
        bool detail_ReadGroupInfo(ulong groupId, GroupInfo* info) const;
        bool detail_ReadGroupItemInfo(ulong groupId, ulong index, GroupItemInfo* info) const;
        bool detail_ReadFileInfo(ulong fileId, FileInfo* info) const;
        bool detail_ReadFilePos(ulong fileId, ulong index, FilePos* filePos) const;

        // vtable 0x0
        detail::SoundArchiveFileReader* fileReader;
        char extFileRoot[256];
};

} // namespace snd
} // namespace nw4r
