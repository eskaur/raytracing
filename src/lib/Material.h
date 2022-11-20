#pragma once

#include <Ray.h>
#include <Utils.h>
#include <Vec.h>

#include <optional>

namespace Raytracing
{
    struct ScatterResult
    {
        Color3 attenuation;
        Ray scatteredRay;
    };

    class Material
    {
    public:
        virtual std::optional<ScatterResult>
        scatter(const Ray &incomingRay, const Point3 &hitPoint, const Vec3 &hitNormal) const = 0;
    };

    class Lambertian : public Material
    {
    public:
        Lambertian(const Color3 &albedo)
            : m_albedo(albedo){};

        virtual std::optional<ScatterResult>
        scatter(const Ray & /*incomingRay*/, const Point3 &hitPoint, const Vec3 &hitNormal) const override
        {
            auto scatterDirection = hitNormal + random_point_in_unit_sphere();
            if(scatterDirection.near_zero())
            {
                scatterDirection = hitNormal;
            }
            return ScatterResult{ m_albedo, Ray(hitPoint, scatterDirection) };
        }

    private:
        Color3 m_albedo;
    };

} // namespace Raytracing