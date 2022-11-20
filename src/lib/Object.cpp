#include <Object.h>

#include <cmath>

namespace Raytracing
{
    Sphere::Sphere(const Point3 &center, float radius, std::unique_ptr<Material> material)
        : m_center(center)
        , m_radius(radius)
        , m_material(std::move(material))
    {}

    std::optional<HitResult> Sphere::hit(const Ray &ray, float tMin, float tMax) const
    {
        Raytracing::Vec3 oc = ray.origin() - m_center;
        const auto a = ray.direction().length_squared();
        const auto halfb = Raytracing::dot(oc, ray.direction());
        const auto c = oc.length_squared() - m_radius * m_radius;
        const auto discriminant = halfb * halfb - a * c;
        if(discriminant < 0)
        {
            // No hit
            return std::nullopt;
        }
        const auto sqrtd = sqrt(discriminant);
        float root = (-halfb - sqrtd) / a;

        if(root < tMin || root > tMax)
        {
            root = (-halfb + sqrtd) / a;
            if(root < tMin || root > tMax)
            {
                // No hit within range
                return std::nullopt;
            }
        }

        // Valid hit found
        const auto hitPoint = ray.at(root);
        const auto outwardNormal = (hitPoint - m_center) / m_radius;
        return HitResult(ray, hitPoint, outwardNormal, root, m_material.get());
    }

} // namespace Raytracing
