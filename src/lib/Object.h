#pragma once

#include <HitResult.h>
#include <Ray.h>
#include <Vec.h>

#include <memory>
#include <optional>

namespace Raytracing
{
    class Object
    {
    public:
        virtual std::optional<HitResult> hit(const Ray &ray, float tMin, float tMax) const = 0;
    };

    class ObjectGroup : public Object
    {
    public:
        virtual std::optional<HitResult> hit(const Ray &ray, float tMin, float tMax) const override;
        void addObject(std::unique_ptr<Object> object);

    private:
        std::vector<std::unique_ptr<Object>> m_objects;
    };

    class Sphere final : public Object
    {
    public:
        Sphere(const Point3 &center, float radius, std::unique_ptr<Material> material);
        virtual std::optional<HitResult> hit(const Ray &ray, float tMin, float tMax) const final override;

    private:
        Point3 m_center;
        float m_radius;
        std::unique_ptr<Material> m_material;
    };

    template<int idxA, int idxB, int idxC>
    class AlignedRect final : public Object
    {
    public:
        AlignedRect(const Point3 &center, float sizeA, float sizeB, std::unique_ptr<Material> material)
            : m_minA(center[idxA] - sizeA / 2)
            , m_maxA(center[idxA] + sizeA / 2)
            , m_minB(center[idxB] - sizeB / 2)
            , m_maxB(center[idxB] + sizeB / 2)
            , m_posC(center[idxC])
            , m_material(std::move(material))
        {}

        virtual std::optional<HitResult> hit(const Ray &ray, float tMin, float tMax) const final override;

    private:
        float m_minA;
        float m_maxA;
        float m_minB;
        float m_maxB;
        float m_posC;
        std::unique_ptr<Material> m_material;
    };

    using XYRect = AlignedRect<0, 1, 2>;
    using XZRect = AlignedRect<0, 2, 1>;
    using YZRect = AlignedRect<1, 2, 0>;

    class Box final : public ObjectGroup
    {
    public:
        Box(const Point3 &center, Vec3 size, std::unique_ptr<Material> material);
    };

} // namespace Raytracing
