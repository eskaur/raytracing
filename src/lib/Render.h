#pragma once

#include <Image.h>
#include <Ray.h>
#include <Scene.h>
#include <Vec.h>

namespace Raytracing
{
    class Renderer
    {
    public:
        Renderer(float viewportHeight, float viewportWidth, float focalLength);
        void render(Image &image, const Scene &scene);

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