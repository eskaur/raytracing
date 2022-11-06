#pragma once

#include <Image.h>
#include <Ray.h>
#include <Vec.h>

#include <functional>

namespace Raytracing
{
    class Renderer
    {
    public:
        Renderer(float viewportHeight, float viewportWidth, float focalLength);
        void render(Image &image, std::function<Color3(Ray)> renderFunc);

    private:
        float m_viewportHeight;
        float m_viewportWidth;
        float m_focalLength;
        Point3 m_origin;
        Vec3 m_horizontal;
        Vec3 m_vertical;
        Vec3 m_lowerLeftCorner;
    };
} // namespace Raytracing