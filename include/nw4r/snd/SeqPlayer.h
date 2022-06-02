#include <kamek.h>

namespace nw4r {
namespace snd {

struct SeqUserprocCallbackParam {
    vs16* localVariable;
    vs16* globalVariable;
    vs16* trackVariable;
    bool cmpFlag;
};

typedef void (*SeqUserprocCallback)(u16 procId, SeqUserprocCallbackParam* param, void* arg);

} // namespace snd
} // namespace nw4r
