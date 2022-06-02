#include <nw4r/snd/BasicSound.h>
#include <nw4r/snd/ExternalSoundPlayer.h>
#include <nw4r/snd/SoundStartable.h>

namespace nw4r {
namespace snd {

class SoundArchivePlayer;

class SoundActor : public SoundStartable {
    public:
        SoundArchivePlayer& soundArchivePlayer;
        detail::ExternalSoundPlayer actorPlayer[4];
        detail::SoundActorParam actorParam;
};

} // namespace snd
} // namespace nw4r
