#include <Scene.h>

#include <Utils.h>

#include <limits>

namespace Raytracing
{
    namespace
    {
        Point3 randomPoint(float min, float max)
        {
            return Point3(random(min, max), random(min, max), random(min, max));
        }

        Point3 random_point_in_unit_sphere()
        {
            while(true)
            {
                const auto p = randomPoint(-1, 1);
                if(p.length_squared() >= 1)
                {
                    continue;
                }
                return p;
            }
        }
    } // namespace

    void Scene::addObject(std::unique_ptr<Object> object)
    {
        m_objects.push_back(std::move(object));
    }

    Color3 Scene::shootRay(const Ray &ray, int depth) const
    {
        if(depth <= 0)
        {
            return Color3(0.0F, 0.0F, 0.0F);
        }

        const float tMin = 0.001F;
        const float tMax = std::numeric_limits<float>::infinity();

        std::optional<HitResult> closestHit;
        float tClosest = tMax;

        for(const auto &object : m_objects)
        {
            if(const auto hit = object->hit(ray, tMin, tClosest))
            {
                // Found a hit closer than the closest so far
                tClosest = hit->t;
                closestHit = hit;
            }
        }

        if(closestHit.has_value())
        {
            const Point3 target = closestHit->point + closestHit->normal + random_point_in_unit_sphere();
            const auto ray = Ray(closestHit->point, target - closestHit->point);
            return 0.5 * shootRay(ray, depth - 1);
        }

        // No hit. Draw background
        const Vec3 unitDirection = unit_vector(ray.direction());
        const float t1 = 0.5 * (unitDirection.y() + 1.0);
        return (1.0F - t1) * Color3(1.0F, 1.0F, 1.0F) + t1 * Color3(0.5F, 0.7F, 1.0F);
    }

} // namespace Raytracing
