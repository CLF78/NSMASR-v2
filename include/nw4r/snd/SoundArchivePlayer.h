#pragma once
#include <kamek.h>
#include <nw4r/snd/DisposeCallbackManager.h>
#include <nw4r/snd/MmlParser.h>
#include <nw4r/snd/MmlSeqTrackAllocator.h>
#include <nw4r/snd/NoteOnCallback.h>
#include <nw4r/snd/SeqPlayer.h>
#include <nw4r/snd/SeqTrackAllocator.h>
#include <nw4r/snd/SoundArchive.h>
#include <nw4r/snd/SoundInstanceManager.h>
#include <nw4r/snd/SoundMemoryAllocatable.h>
#include <nw4r/snd/SoundPlayer.h>
#include <nw4r/snd/SoundStartable.h>
#include <nw4r/snd/StrmChannel.h>
#include <nw4r/snd/WsdPlayer.h>

namespace nw4r {
namespace snd {

namespace detail {
class SoundArchivePlayer_FileManager {
    public:
        void* vtable;
};
} // namespace detail

class SoundArchivePlayer : public detail::DisposeCallback, public SoundStartable {
    public:
        class SeqNoteOnCallback : public detail::NoteOnCallback {
            public:
                const SoundArchivePlayer& mSoundArchivePlayer;
        };

        class WsdCallback : public detail::WsdPlayer::WsdCallback {
            public:
                const SoundArchivePlayer& mSoundArchivePlayer;
        };

        struct GroupAddress {
            const void* address;
            const void* waveDataAddress;
        };

        struct FileAddress {
            const void* address;
            const void* waveDataAddress;
        };

        bool IsAvailable() const;

        bool LoadGroup(ulong groupId, SoundMemoryAllocatable* allocater, ulong loadBlockSize = 0);

        const void* detail_GetFileAddress(u32 fileId) const;
        const void* detail_GetFileWaveDataAddress(u32 fileId) const;

        const SoundArchive* soundArchive;
        detail::Util::Table<GroupAddress>* groupTable;
        detail::Util::Table<FileAddress>* fileTable;
        detail::SoundArchivePlayer_FileManager* fileManager;

        // Callback
        SeqNoteOnCallback seqCallback;
        WsdCallback wsdCallback;
        detail::SeqTrackAllocator* seqTrackAllocator;
        SeqUserprocCallback seqUserprocCallback;
        void* seqUserprocCallbackArg;

        // Sound Player
        ulong soundPlayerCount;
        SoundPlayer* soundPlayers;

        // Manager/allocator
        detail::SoundInstanceManager seqSoundInstanceManager;
        detail::SoundInstanceManager strmSoundInstanceManager;
        detail::SoundInstanceManager waveSoundInstanceManager;
        detail::MmlSeqTrackAllocator mmlSeqTrackAllocator; // default sequence track allocator
        detail::StrmBufferPool strmBufferPool;

        // Default sequence spacer
        detail::MmlParser mmlParser;

        // Record the buffer information
        void* setupBufferAddress;
        ulong setupBufferSize;
};

} // namespace snd
} // namespace nw4r
