#include <kamek.h>
#include <rvl/os/OSContext.h>

namespace nw4r {
namespace db {

void Exception_Printf_(const char* format, ...);
void ShowMainInfo_(u16 error, const OSContext* context, ulong dsisr, ulong dar);

} // namespace db
} // namespace nw4r
