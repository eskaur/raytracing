#pragma once

#include <array>
#include <iosfwd>
#include <string>

namespace Raytracing
{
    class Vec3
    {
    public:
        Vec3();
        Vec3(float e0, float e1, float e2);

        float x() const;
        float y() const;
        float z() const;

        Vec3 operator-() const;
        float operator[](int i) const;
        float &operator[](int i);
        Vec3 &operator+=(const Vec3 &v);
        Vec3 &operator*=(const float t);
        Vec3 &operator/=(const float t);

        float length() const;
        float length_squared() const;

        std::string toString() const;

    private:
        std::array<float, 3> e;
    };

    Vec3 operator+(const Vec3 &u, const Vec3 &v);
    Vec3 operator-(const Vec3 &u, const Vec3 &v);
    Vec3 operator*(const Vec3 &u, const Vec3 &v);
    Vec3 operator*(float t, const Vec3 &v);
    Vec3 operator*(const Vec3 &v, float t);
    Vec3 operator/(Vec3 v, float t);
    float dot(const Vec3 &u, const Vec3 &v);
    Vec3 cross(const Vec3 &u, const Vec3 &v);
    Vec3 unit_vector(Vec3 v);
    std::ostream &operator<<(std::ostream &stream, const Vec3 &v);

} // namespace Raytracing