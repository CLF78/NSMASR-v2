#include <nw4r/ut/utList.h>

namespace nw4r {
namespace snd {

class SoundPlayer {
    public:
        ut::LinkListImpl soundList;
        ut::LinkListImpl priorityList;
        ut::LinkListImpl heapList;

        int playableCount;
        int playableLimit;

        float volume;
        float lpfFreq;
        int outputLineFlag;
        float mainOutVolume;
        int biquadType;
        float biquadValue;
        float remoteOutVolume[4];
        float mainSend;
        float fxSend[3];
};

} // namespace snd
} // namespace nw4r
