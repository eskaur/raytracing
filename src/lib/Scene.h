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
        Scene();
        Color3 shootRay(const Ray &ray, int depth) const;
        void addObject(std::unique_ptr<Object> object);

    private:
        ObjectGroup m_rootObjectGroup;
        const float m_tMin;
        const float m_tMax;
    };

} // namespace Raytracing
