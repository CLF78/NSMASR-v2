#include <kamek.h>
#include <nw4r/g3d/camera.h>

namespace m3d {

u8 getCurrentCameraID();
nw4r::g3d::Camera getCamera(int id);
nw4r::g3d::Camera getCurrentCamera();

} // namespace m3d
