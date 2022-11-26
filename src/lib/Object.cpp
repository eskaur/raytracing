#include <Object.h>

#include <cmath>

namespace Raytracing
{
    namespace
    {
        std::optional<HitResult> rectangleHit(
            const Ray &ray,
            float tMin,
            float tMax,
            int idxA,
            int idxB,
            int idxC,
            float minA,
            float maxA,
            float minB,
            float maxB,
            float posC,
            const std::unique_ptr<Material> &material)
        {
            if(ray.direction()[idxC] == 0.0F)
            {
                return std::nullopt;
            }

            const float tPlaneHit = (posC - ray.origin()[idxC]) / ray.direction()[idxC];

            if(tPlaneHit < tMin || tPlaneHit > tMax)
            {
                return std::nullopt;
            }

            const auto hitPoint = ray.at(tPlaneHit);
            const float planeHitA = hitPoint[idxA];
            const float planeHitB = hitPoint[idxB];

            if(planeHitA < minA || planeHitA > maxA || planeHitB < minB || planeHitB > maxB)
            {
                return std::nullopt;
            }

            // Valid hit found
            auto outwardNormal = Point3(0, 0, 0);
            outwardNormal[idxC] = 1.0F;
            return HitResult(ray, hitPoint, outwardNormal, tPlaneHit, material.get());
        }
    } // namespace

    Object::Object(std::unique_ptr<Material> material)
        : m_material(std::move(material))
    {}

    Sphere::Sphere(const Point3 &center, float radius, std::unique_ptr<Material> material)
        : Object(std::move(material))
        , m_center(center)
        , m_radius(radius)
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

    template<>
    std::optional<HitResult> XYRect::hit(Raytracing::Ray const &ray, float tMin, float tMax) const
    {
        return rectangleHit(ray, tMin, tMax, 0, 1, 2, m_minA, m_maxA, m_minB, m_maxB, m_posC, m_material);
    }

    template<>
    std::optional<HitResult> XZRect::hit(Raytracing::Ray const &ray, float tMin, float tMax) const
    {
        return rectangleHit(ray, tMin, tMax, 0, 2, 1, m_minA, m_maxA, m_minB, m_maxB, m_posC, m_material);
    }

    template<>
    std::optional<HitResult> YZRect::hit(Raytracing::Ray const &ray, float tMin, float tMax) const
    {
        return rectangleHit(ray, tMin, tMax, 1, 2, 0, m_minA, m_maxA, m_minB, m_maxB, m_posC, m_material);
    }

} // namespace Raytracing
