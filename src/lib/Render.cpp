#include <Render.h>

#include <Ray.h>
#include <Utils.h>

#include <iostream>

namespace Raytracing
{
    Renderer::Renderer(float viewportHeight, float viewportWidth, float focalLength)
        : m_viewportHeight(viewportHeight)
        , m_viewportWidth(viewportWidth)
        , m_focalLength(focalLength)
        , m_origin(0.0F, 0.0F, 0.0F)
        , m_horizontal(m_viewportWidth, 0.0F, 0.0F)
        , m_vertical(0, m_viewportHeight, 0)
        , m_lowerLeftCorner(m_origin - m_horizontal / 2 - m_vertical / 2 - Raytracing::Vec3(0, 0, m_focalLength))
    {}

    void Renderer::render(Image &image, const Scene &scene)
    {
        constexpr int maxDepth = 20;
        constexpr int samplesPerPixel = 64;

        for(int i = 0; i < image.height(); ++i)
        {
            std::cout << "Rendering line: " << i << std::endl;

#pragma omp parallel for
            for(int j = 0; j < image.width(); ++j)
            {
                Color3 color(0, 0, 0);

                for(int s = 0; s < samplesPerPixel; ++s)
                {
                    const auto u = float(j + random()) / (image.width() - 1);
                    const auto v = float(i + random()) / (image.height() - 1);
                    const Ray ray(m_origin, m_lowerLeftCorner + u * m_horizontal + v * m_vertical - m_origin);
                    color += scene.shootRay(ray, maxDepth);
                }

                image(i, j) = color / samplesPerPixel;
            }
        }
        std::cout << "\nDone.\n";
    }
} // namespace Raytracing