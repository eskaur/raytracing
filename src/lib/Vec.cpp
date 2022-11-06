#include <Vec.h>

#include <cmath>
#include <sstream>

namespace Raytracing
{
    Vec3::Vec3()
        : e{ 0.0F, 0.0F, 0.0F }
    {}

    Vec3::Vec3(float e0, float e1, float e2)
        : e{ e0, e1, e2 }
    {}

    float Vec3::x() const
    {
        return e[0];
    }
    float Vec3::y() const
    {
        return e[1];
    }
    float Vec3::z() const
    {
        return e[2];
    }

    Vec3 Vec3::operator-() const
    {
        return Vec3{ -x(), -y(), -z() };
    }

    float Vec3::operator[](int i) const
    {
        return e[i];
    }

    float &Vec3::operator[](int i)
    {
        return e[i];
    }

    Vec3 &Vec3::operator+=(const Vec3 &v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    Vec3 &Vec3::operator*=(const float t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    Vec3 &Vec3::operator/=(const float t)
    {
        return (*this) *= 1 / t;
    }

    float Vec3::length() const
    {
        return std::sqrt(length_squared());
    }

    float Vec3::length_squared() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    std::string Vec3::toString() const
    {
        std::stringstream stream;
        stream << "[" << x() << ", " << y() << ", " << z() << "]";
        return stream.str();
    }

    Vec3 operator+(const Vec3 &u, const Vec3 &v)
    {
        return Vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
    }

    Vec3 operator-(const Vec3 &u, const Vec3 &v)
    {
        return Vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
    }

    Vec3 operator*(const Vec3 &u, const Vec3 &v)
    {
        return Vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
    }

    Vec3 operator*(float t, const Vec3 &v)
    {
        return Vec3(t * v.x(), t * v.y(), t * v.z());
    }

    Vec3 operator*(const Vec3 &v, float t)
    {
        return t * v;
    }

    Vec3 operator/(Vec3 v, float t)
    {
        return Vec3(v.x() / t, v.y() / t, v.z() / t);
    }

    float dot(const Vec3 &u, const Vec3 &v)
    {
        return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
    }

    Vec3 cross(const Vec3 &u, const Vec3 &v)
    {
        return Vec3(
            u.y() * v.z() - u.z() * v.y(), //
            u.z() * v.x() - u.x() * v.z(), //
            u.x() * v.y() - u.y() * v.x()  //
        );
    }

    Vec3 unit_vector(Vec3 v)
    {
        return v / v.length();
    }

    std::ostream &operator<<(std::ostream &stream, const Vec3 &v)
    {
        return stream << v.toString();
    }

    Point3 operator+(const Point3 &p, const Vec3 &v)
    {
        return Point3(p.x() + v.x(), p.y() + v.y(), p.z() + v.z());
    }

    Color3 operator*(float t, const Color3 &c)
    {
        return Color3(t * c.x(), t * c.y(), t * c.z());
    }

    Color3 operator+(const Color3 &u, const Color3 &v)
    {
        return Color3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
    }

    Color3 operator-(const Color3 &u, const Color3 &v)
    {
        return Color3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
    }

    Vec3 operator-(const Point3 &u, const Point3 &v)
    {
        return Vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
    }

} // namespace Raytracing