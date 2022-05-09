#pragma once
#include <kamek.h>
#include <nw4r/snd/DisposeCallbackManager.h>
#include <nw4r/snd/NoteOnCallback.h>
#include <nw4r/snd/SeqPlayer.h>
#include <nw4r/snd/SeqTrackAllocator.h>
#include <nw4r/snd/SoundArchive.h>
#include <nw4r/snd/SoundPlayer.h>
#include <nw4r/snd/SoundStartable.h>
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

        const SoundArchive* soundArchive;
        detail::Util::Table<GroupAddress>* groupTable;
        detail::Util::Table<FileAddress>* mFileTable;
        detail::SoundArchivePlayer_FileManager* mFileManager;

        // Callback
        SeqNoteOnCallback mSeqCallback;
        WsdCallback mWsdCallback;
        detail::SeqTrackAllocator* mSeqTrackAllocator;
        SeqUserprocCallback mSeqUserprocCallback;
        void* mSeqUserprocCallbackArg;

        // Sound Player
        ulong mSoundPlayerCount;
        SoundPlayer* mSoundPlayers;

		// TODO: Fill these out
        // Manager/allocator
        detail::SeqSoundInstanceManager mSeqSoundInstanceManager;
        detail::StrmSoundInstanceManager mStrmSoundInstanceManager;
        detail::WaveSoundInstanceManager mWaveSoundInstanceManager;
        detail::MmlSeqTrackAllocator mMmlSeqTrackAllocator; // default sequence track allocator
        detail::StrmBufferPool mStrmBufferPool;

        // Default sequence spacer
        detail::MmlParser mMmlParser;

        // Record the buffer information
        void* mSetupBufferAddress;
        unsigned long mSetupBufferSize;
};

} // namespace detail
} // namespace snd
} // namespace nw4r
