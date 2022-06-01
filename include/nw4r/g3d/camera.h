#pragma once
#include <kamek.h>
#include <nw4r/g3d/res/rescommon.h>

namespace nw4r {
namespace g3d {

struct CameraData {
    MTX34 cameraMtx;
    MTX44 projMtx;

    u32 flags;

    // Camera
    VEC3 cameraPos;
    VEC3 cameraUp;
    VEC3 cameraViewpoint;
    VEC3 cameraRotation;
    f32 cameraTwist; // Same as the Z component of the rotation amount

    // Projection
    GXProjectionType::Value projType;
    f32 projFovy;
    f32 projAspect;
    f32 projNear;
    f32 projFar;
    f32 projTop;
    f32 projBottom;
    f32 projLeft;
    f32 projRight;

    f32 lightScaleS;
    f32 lightScaleT;
    f32 lightTransS;
    f32 lightTransT;

    // Viewport
    VEC2 viewportOrigin;
    VEC2 viewportSize;
    f32 viewportNear;
    f32 viewportFar;

    // Scissor box
    u32 scissorX;
    u32 scissorY;
    u32 scissorWidth;
    u32 scissorHeight;

    s32 scissorOffsetX;
    s32 scissorOffsetY;
};

class Camera : public ResCommon<CameraData> {
    public:
        void GetCameraMtx(MTX34* pMtx) const;
};

} // namespace g3d
} // namespace nw4r
