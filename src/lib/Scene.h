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
        void addObject(std::unique_ptr<Object> object);
        Color3 shootRay(const Ray &ray, int depth) const;

    private:
        std::vector<std::unique_ptr<Object>> m_objects;
    };

} // namespace Raytracing
