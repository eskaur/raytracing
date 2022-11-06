#include <Scene.h>

#include <limits>

namespace Raytracing
{
    void Scene::addObject(std::unique_ptr<Object> object)
    {
        m_objects.push_back(std::move(object));
    }

    Color3 Scene::shootRay(const Ray &ray)
    {
        const float tMin = 0.0F;
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
            const auto &n = closestHit->normal;
            return 0.5 * Color3(n.x() + 1, n.y() + 1, n.z() + 1);
        }

        // No hit. Draw background
        const Vec3 unitDirection = unit_vector(ray.direction());
        const float t1 = 0.5 * (unitDirection.y() + 1.0);
        return (1.0F - t1) * Color3(1.0F, 1.0F, 1.0F) + t1 * Color3(0.5F, 0.7F, 1.0F);
    }

} // namespace Raytracing
