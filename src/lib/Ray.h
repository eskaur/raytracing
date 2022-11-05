#pragma once

#include <Vec.h>

namespace Raytracing
{
    class Ray
    {
    public:
        Ray();
        Ray(const Point3 &origin, const Vec3 &direction);

        Point3 origin() const;
        Vec3 direction() const;
        Point3 at(float t) const;

    private:
        Point3 m_origin;
        Vec3 m_direction;
    };
} // namespace Raytracing