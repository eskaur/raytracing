#include <Camera.h>

#include <iostream>

namespace Raytracing
{
    Camera::Camera(float aspectRatio, size_t pixelHeight, float viewportHeight, float focalLength)
        : m_pixelHeight(pixelHeight)
        , m_pixelWidth(aspectRatio * pixelHeight)
        , m_viewportHeight(viewportHeight)
        , m_viewportWidth(aspectRatio * viewportHeight)
        , m_focalLength(focalLength){};

    Image Camera::render(const Scene &scene) const
    {
        Image image(m_pixelHeight, m_pixelWidth);

        const auto origin = Point3(0.0F, 0.0F, 0.0F);
        const auto horizontal = Vec3(m_viewportWidth, 0.0F, 0.0F);
        const auto vertical = Vec3(0, m_viewportHeight, 0);
        const auto lowerLeftCorner(origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, m_focalLength));

        constexpr int maxDepth = 20;
        constexpr int samplesPerPixel = 64;

#pragma omp parallel for schedule(dynamic)
        for(int i = 0; i < image.height(); ++i)
        {
            std::cout << "Rendering line: " << i << std::endl;

            for(int j = 0; j < image.width(); ++j)
            {
                Color3 color(0, 0, 0);

                for(int s = 0; s < samplesPerPixel; ++s)
                {
                    const auto u = float(j + random()) / (image.width() - 1);
                    const auto v = float(i + random()) / (image.height() - 1);
                    const Ray ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
                    color += scene.shootRay(ray, maxDepth);
                }

                image(i, j) = color / samplesPerPixel;
            }
        }
        std::cout << "\nDone.\n";
        return image;
    }

} // namespace Raytracing
