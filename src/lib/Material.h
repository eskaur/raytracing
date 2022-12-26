#pragma once

#include <Ray.h>
#include <Utils.h>
#include <Vec.h>

#include <memory>
#include <optional>

namespace Raytracing
{
    struct ScatterResult
    {
        Color3 attenuation;
        Ray scatteredRay;
    };

    struct EmissionResult
    {
        Color3 color;
    };

    class Material
    {
    public:
        virtual std::optional<ScatterResult>
        scatter(const Ray &incomingRay, const Point3 &hitPoint, const Vec3 &hitNormal) const = 0;

        virtual EmissionResult emit() const
        {
            return EmissionResult{ Color3(0.0F, 0.0F, 0.0F) };
        }

        virtual std::unique_ptr<Material> clone() const = 0;
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

        virtual std::unique_ptr<Material> clone() const
        {
            return std::make_unique<Lambertian>(*this);
        }

    private:
        Color3 m_albedo;
    };

    class Metal : public Material
    {
    public:
        Metal()
            : Metal(Color3(0.8, 0.8F, 0.8F), 0.05F)
        {}

        Metal(const Color3 &albedo)
            : Metal(albedo, 0.05F)
        {}

        Metal(const Color3 &albedo, float roughness)
            : m_albedo(albedo)
            , m_roughness(roughness)
        {
            if(m_roughness < 0 || m_roughness >= 1)
            {
                throw std::runtime_error("Roughness must be in [0,1)");
            }
        }

        virtual std::optional<ScatterResult>
        scatter(const Ray &incomingRay, const Point3 &hitPoint, const Vec3 &hitNormal) const override
        {
            const auto v = unit_vector(incomingRay.direction());
            const auto reflectedDirection = v - 2 * dot(v, hitNormal) * hitNormal;
            const auto scatteredRay = Ray(hitPoint, reflectedDirection + m_roughness * random_point_in_unit_sphere());
            if(dot(scatteredRay.direction(), hitNormal) <= 0.0F)
            {
                return std::nullopt;
            }
            return ScatterResult{ m_albedo, scatteredRay };
        }

        virtual std::unique_ptr<Material> clone() const
        {
            return std::make_unique<Metal>(*this);
        }

    private:
        Color3 m_albedo;
        float m_roughness;
    };

    class DiffuseLight : public Material
    {
    public:
        DiffuseLight(const Color3 color)
            : m_color(color)
        {}

        virtual std::optional<ScatterResult> scatter(const Ray &, const Point3 &, const Vec3 &) const override
        {
            return std::nullopt;
        }

        virtual EmissionResult emit() const override
        {
            return EmissionResult{ m_color };
        }

        virtual std::unique_ptr<Material> clone() const
        {
            return std::make_unique<DiffuseLight>(*this);
        }

    private:
        Color3 m_color;
    };

} // namespace Raytracing