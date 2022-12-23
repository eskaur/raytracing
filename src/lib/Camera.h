#pragma once

#include <Image.h>
#include <Scene.h>
#include <Vec.h>

namespace Raytracing
{
    class Camera
    {
    public:
        Camera(
            const Point3 &origin,
            const Point3 &lookAt,
            float focusDist,
            float aspectRatio,
            size_t pixelHeight,
            float verticalFovDegrees,
            float lensRadius);
        Image render(const Scene &scene) const;

    private:
        const Point3 m_origin;
        const Vec3 m_lookDir;
        const size_t m_pixelHeight;
        const size_t m_pixelWidth;
        const float m_focusDist;
        const float m_focalPlaneHeight;
        const float m_focalPlaneWidth;
        const float m_lensRadius;
    };
} // namespace Raytracing