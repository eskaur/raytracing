#pragma once

#include <Ray.h>
#include <Vec.h>

#include <optional>

namespace Raytracing
{
    struct HitResult
    {
        HitResult(const Ray &ray, const Point3 &point_, const Vec3 &outwardNormal, float t_)
            : point(point_)
            , isFrontFace(dot(ray.direction(), outwardNormal) < 0)
            , normal(isFrontFace ? outwardNormal : -outwardNormal)
            , t(t_)
        {}

        Point3 point;
        bool isFrontFace;
        Vec3 normal;
        float t;
    };

    class Object
    {
    public:
        virtual std::optional<HitResult> hit(const Ray &ray, float tMin, float tMax) const = 0;
    };

    class Sphere : public Object
    {
    public:
        Sphere(const Point3 &center, float radius);
        virtual std::optional<HitResult> hit(const Ray &ray, float tMin, float tMax) const override;

    private:
        Point3 m_center;
        float m_radius;
    };

} // namespace Raytracing
