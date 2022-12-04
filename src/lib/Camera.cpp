#include <Camera.h>

#include <cmath>
#include <iostream>

namespace
{
    constexpr float focalLength = 1.0F;
    constexpr float pi = 3.1415926535897932385;

    float deg2rad(float deg)
    {
        return deg * pi / 180.0F;
    }

} // namespace

namespace Raytracing
{
    Camera::Camera(float aspectRatio, size_t pixelHeight, float verticalFovDegrees)
        : m_pixelHeight(pixelHeight)
        , m_pixelWidth(aspectRatio * pixelHeight)
        , m_viewportHeight(2.0F * focalLength * std::tan(0.5F * deg2rad(verticalFovDegrees)))
        , m_viewportWidth(aspectRatio * m_viewportHeight)
    {
        if(aspectRatio <= 0.0)
        {
            throw std::runtime_error("aspectRatio must be a nonzero positive number");
        }
        if(verticalFovDegrees <= 0 || verticalFovDegrees >= 180)
        {
            throw std::runtime_error("verticalFovDegrees must be inside the range (0,180)");
        }
    };

    Image Camera::render(const Scene &scene) const
    {
        Image image(m_pixelHeight, m_pixelWidth);

        const auto origin = Point3(0.0F, 0.0F, 0.0F);
        const auto horizontal = Vec3(m_viewportWidth, 0.0F, 0.0F);
        const auto vertical = Vec3(0, m_viewportHeight, 0);
        const auto lowerLeftCorner(origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focalLength));

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
