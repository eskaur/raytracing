#pragma once

#include <Image.h>
#include <Scene.h>

namespace Raytracing
{
    class Camera
    {
    public:
        Camera(float aspectRatio, size_t pixelHeight, float verticalFovDegrees);
        Image render(const Scene &scene) const;

    private:
        const size_t m_pixelHeight;
        const size_t m_pixelWidth;
        const float m_viewportHeight;
        const float m_viewportWidth;
    };
} // namespace Raytracing