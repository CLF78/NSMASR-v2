#pragma once
#include <egg/core/eggDisposer.h>
#include <nw4r/ut/utList.h>

class SndSceneMgr : public EGG::Disposer {
    public:
        struct SndSceneId {
            enum Value {
                Boot,
                Unk1,
                Unk2,
                TitleOrReplay,
                Unk4,
                Menu,
                MultiCourseSelect,
                Unk7,
                World1,
                World2,
                World3,
                World4,
                World5,
                World6,
                World7,
                World8,
                World9,
                Stage,
                GameOver,
                Results,
                GameOverMultiplayer,
                Movie1,
                Movie2,
                Movie3,
            };
        };

        struct VolumeControl {
            enum Value {
                None,
                FSDuringCopyDeletion, // and possibly more
                WorldmapPauseMenu,
                WorldSelectMenu,
                StockItemMenu,
                Unk5, // used in wmap command 80
                ViewMap,
                ReturnToFSPrompt, // from extra modes
                HintMovieMenu,
                Unk9,
            };
        };

        struct MinigameStage {
            enum Value {
                None,
                MetToad,
                RulesAppear,
                MinigameStart,
                HitOneKoopa,
                HitOneKoopaPlusJr,
                HitTwoKoopas,
                WonPowerupPanels,
                PrizesPowerupPanels,
                NoPrizes,
                Prizes1UPBlast,
            };
        };

        u32 prevSoundSceneId; // see enum
        u32 soundSceneId; // see enum
        u32 _18; // unused?

        u16 bitfield; // &1 = main bgm, &4 = star, &8 = switch bgm, &0x10 = fast bgm, &0x200 = yoshi drums, &0x400 = ??, &0x800 = something boss
        u8 prevMusicControl; // ??
        u8 musicControl; // 0 = stop all music, 1 = stop star music and resume bgm (?), 2 = stop all music and start dummy brstm (?), 4 = start star music, 8 = start switch music
        u8 trackBitFlag; // ??
        // 3 bytes padding

        u32 modulation; // from level settings
        u32 menuMusicStage; // keeps track of which channels need to be played
        u32 minigameStage; // see enum, values 11-15 unused

        u8 bitfield2; // &1 = opening/closing a window, &2 = ??, &4 = game paused, &8 = home menu, &0x10 = system error, &0x20 = system warning
        // 3 bytes padding

        u32 volumeControl; // Used to apply volume adjustments, see enum for meanings and 8019CB40 for exact values
        bool isFastMusic;
        bool _39; // unused?
        bool _3A; // unused?
        bool isToadHouse;
        bool _3C; // something with disableStart, no idea; set for many music ids
        bool noFadeIn; // disables the fade in when exiting the pause menu, the home menu and system warnings; the fade in is always enabled for drums and bowser music ids
        bool disableMusic; // disables bgm when exiting the pause menu, the home menu and system warnings
        bool isWorldMap;

        u32 _40; // unused?
        bool bossFlag; // refer to the zone setting with this name
        // 3 bytes padding

        nw4r::ut::List _48; // unused?
        u32 _54; // unused?

        static SndSceneMgr* sInstance;
};
