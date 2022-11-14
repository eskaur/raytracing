#pragma once

#include <HitResult.h>
#include <Ray.h>
#include <Vec.h>

#include <memory>
#include <optional>

namespace Raytracing
{
    class Object
    {
    public:
        virtual std::optional<HitResult> hit(const Ray &ray, float tMin, float tMax) const = 0;
    };

    class Sphere : public Object
    {
    public:
        Sphere(const Point3 &center, float radius, std::unique_ptr<Material> material);
        virtual std::optional<HitResult> hit(const Ray &ray, float tMin, float tMax) const override;

    private:
        Point3 m_center;
        float m_radius;
        std::unique_ptr<Material> m_material;
    };

} // namespace Raytracing
