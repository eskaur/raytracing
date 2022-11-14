#pragma once

#include <Material.h>
#include <Ray.h>
#include <Vec.h>

namespace Raytracing
{
    struct HitResult
    {
        HitResult(const Ray &ray, const Point3 &point_, const Vec3 &outwardNormal, float t_, Material *material_)
            : point(point_)
            , isFrontFace(dot(ray.direction(), outwardNormal) < 0)
            , normal(isFrontFace ? outwardNormal : -outwardNormal)
            , t(t_)
            , material(material_)
        {}

        Point3 point;
        bool isFrontFace;
        Vec3 normal;
        float t;
        Material *material;
    };
} // namespace Raytracing