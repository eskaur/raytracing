#include <Render.h>

#include <Ray.h>

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

    void Renderer::render(Image &image, std::function<Color3(Ray)> renderFunc)
    {
        for(size_t i = 0; i < image.height(); ++i)
        {
            std::cout << "Rendering line: " << i << std::endl;
            for(size_t j = 0; j < image.width(); ++j)
            {
                const auto u = float(j) / (image.width() - 1);
                const auto v = float(i) / (image.height() - 1);

                const Ray ray(m_origin, m_lowerLeftCorner + u * m_horizontal + v * m_vertical - m_origin);

                image(i, j) = renderFunc(ray);
            }
        }
        std::cout << "\nDone.\n";
    }
} // namespace Raytracing