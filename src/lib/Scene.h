#pragma once

#include <Object.h>
#include <Ray.h>
#include <Vec.h>

#include <memory>
#include <vector>

namespace Raytracing
{
    class Scene
    {
    public:
        Scene(float skyBrightness);
        Color3 shootRay(const Ray &ray, int depth) const;
        void addObject(std::unique_ptr<Object> object);

    private:
        float m_skyBrightness;
        ObjectGroup m_rootObjectGroup;
        const float m_tMin;
        const float m_tMax;
    };

} // namespace Raytracing
