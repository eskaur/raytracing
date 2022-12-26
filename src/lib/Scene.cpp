#include <Scene.h>

#include <Utils.h>

#include <limits>

namespace Raytracing
{
    Scene::Scene(float skyBrightness)
        : m_skyBrightness(skyBrightness)
        , m_rootObjectGroup{}
        , m_tMin(0.001F)
        , m_tMax(std::numeric_limits<float>::infinity())
    {}

    void Scene::addObject(std::unique_ptr<Object> object)
    {
        m_rootObjectGroup.addObject(std::move(object));
    }

    Color3 Scene::shootRay(const Ray &ray, int depth) const
    {
        if(depth <= 0)
        {
            return Color3(0.0F, 0.0F, 0.0F);
        }

        const auto closestHit = m_rootObjectGroup.hit(ray, m_tMin, m_tMax);

        if(closestHit.has_value())
        {
            const auto emissionResult = closestHit->material->emit();

            if(const auto scatterResult = closestHit->material->scatter(ray, closestHit->point, closestHit->normal))
            {
                // Emit and scatter
                return emissionResult.color
                       + scatterResult->attenuation * shootRay(scatterResult->scatteredRay, depth - 1);
            }
            // Pure emission
            return emissionResult.color;
        }

        // No hit. Draw background
        const Vec3 unitDirection = unit_vector(ray.direction());
        const float t1 = 0.5 * (unitDirection.y() + 1.0);
        return m_skyBrightness * ((1.0F - t1) * Color3(1.0F, 1.0F, 1.0F) + t1 * Color3(0.5F, 0.7F, 1.0F));
    }

} // namespace Raytracing
