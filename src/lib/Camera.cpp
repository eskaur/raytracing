#include <Camera.h>

#include <cmath>
#include <iostream>

namespace
{
    constexpr int maxDepth = 20;
    constexpr int samplesPerPixel = 64;
    constexpr float aaBlur = 0.5F;
    constexpr float pi = 3.1415926535897932385;

    float deg2rad(float deg)
    {
        return deg * pi / 180.0F;
    }

} // namespace

namespace Raytracing
{
    Camera::Camera(
        const Point3 &origin,
        const Point3 &lookAt,
        float focusDist,
        float aspectRatio,
        size_t pixelHeight,
        float verticalFovDegrees,
        float lensRadius)
        : m_origin(origin)
        , m_lookDir(unit_vector(lookAt - origin))
        , m_pixelHeight(pixelHeight)
        , m_pixelWidth(aspectRatio * pixelHeight)
        , m_focusDist(focusDist)
        , m_focalPlaneHeight(2.0F * focusDist * std::tan(0.5F * deg2rad(verticalFovDegrees)))
        , m_focalPlaneWidth(aspectRatio * m_focalPlaneHeight)
        , m_lensRadius(lensRadius)
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

        const Vec3 up(0, 1, 0);

        const Vec3 w = unit_vector(-m_lookDir);
        const Vec3 u = unit_vector(cross(up, w));
        const Vec3 v = unit_vector(cross(w, u));

        const Point3 focalPlaneCenter = m_origin + m_focusDist * m_lookDir;

        const Point3 focalPlaneLowerLeftCorner =
            focalPlaneCenter - 0.5F * m_focalPlaneWidth * u - 0.5F * m_focalPlaneHeight * v;

        const float duPixel = m_focalPlaneWidth / (image.width() - 1);
        const float dvPixel = m_focalPlaneHeight / (image.height() - 1);

#pragma omp parallel for schedule(dynamic)
        for(int i = 0; i < image.height(); ++i)
        {
            std::cout << "Rendering line: " << i << std::endl;

            for(int j = 0; j < image.width(); ++j)
            {
                Color3 color(0, 0, 0);

                for(int s = 0; s < samplesPerPixel; ++s)
                {
                    const Vec3 rd = m_lensRadius * random_in_unit_disk();
                    const Vec3 offset = u * rd.x() + v * rd.y();
                    const Point3 newOrigin = m_origin + offset;

                    const float jRandomized = random(j - aaBlur, j + aaBlur);
                    const float iRandomized = random(i - aaBlur, i + aaBlur);
                    const float du = jRandomized * duPixel;
                    const float dv = iRandomized * dvPixel;
                    const Point3 rayFocalPlaneIntersect = focalPlaneLowerLeftCorner + du * u + dv * v;
                    const Ray ray(newOrigin, rayFocalPlaneIntersect - newOrigin);
                    color += scene.shootRay(ray, maxDepth);
                }

                image(i, j) = color / samplesPerPixel;
            }
        }
        std::cout << "\nDone.\n";
        return image;
    }

} // namespace Raytracing
