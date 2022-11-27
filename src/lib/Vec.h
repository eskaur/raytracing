#pragma once

#include <array>
#include <cmath>
#include <iosfwd>
#include <sstream>
#include <string>

namespace Raytracing
{
    class Vec3
    {
    public:
        Vec3()
            : e{ 0.0F, 0.0F, 0.0F } {};
        Vec3(float e0, float e1, float e2)
            : e{ e0, e1, e2 } {};

        float x() const
        {
            return e[0];
        }
        float y() const
        {
            return e[1];
        }
        float z() const
        {
            return e[2];
        }

        Vec3 operator-() const
        {
            return Vec3{ -x(), -y(), -z() };
        }

        float operator[](int i) const
        {
            return e[i];
        }

        float &operator[](int i)
        {
            return e[i];
        }

        Vec3 &operator+=(const Vec3 &v)
        {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        Vec3 &operator*=(const float t)
        {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        Vec3 &operator/=(const float t)
        {
            return (*this) *= 1 / t;
        }

        float length() const
        {
            return std::sqrt(length_squared());
        }

        float length_squared() const
        {
            return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
        }

        bool near_zero() const
        {
            const float s = 1e-6;
            return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
        }

        std::string toString() const
        {
            std::stringstream stream;
            stream << "[" << x() << ", " << y() << ", " << z() << "]";
            return stream.str();
        }

    private:
        std::array<float, 3> e;
    };

    class Color3 : public Vec3
    {
        using Vec3::Vec3;
    };

    class Point3 : public Vec3
    {
        using Vec3::Vec3;
    };

    inline Vec3 operator+(const Vec3 &u, const Vec3 &v)
    {
        return Vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
    }

    inline Vec3 operator-(const Vec3 &u, const Vec3 &v)
    {
        return Vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
    }

    inline Vec3 operator*(const Vec3 &u, const Vec3 &v)
    {
        return Vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
    }

    inline Vec3 operator*(float t, const Vec3 &v)
    {
        return Vec3(t * v.x(), t * v.y(), t * v.z());
    }

    inline Vec3 operator*(const Vec3 &v, float t)
    {
        return t * v;
    }

    inline Vec3 operator/(Vec3 v, float t)
    {
        return Vec3(v.x() / t, v.y() / t, v.z() / t);
    }

    inline float dot(const Vec3 &u, const Vec3 &v)
    {
        return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
    }

    inline Vec3 cross(const Vec3 &u, const Vec3 &v)
    {
        return Vec3(
            u.y() * v.z() - u.z() * v.y(), //
            u.z() * v.x() - u.x() * v.z(), //
            u.x() * v.y() - u.y() * v.x()  //
        );
    }

    inline Vec3 unit_vector(Vec3 v)
    {
        return v / v.length();
    }

    inline std::ostream &operator<<(std::ostream &stream, const Vec3 &v)
    {
        return stream << v.toString();
    }

    inline Point3 operator+(const Point3 &p, const Vec3 &v)
    {
        return Point3(p.x() + v.x(), p.y() + v.y(), p.z() + v.z());
    }

    inline Point3 operator-(const Point3 &p, const Vec3 &v)
    {
        return Point3(p.x() - v.x(), p.y() - v.y(), p.z() - v.z());
    }

    inline Color3 operator*(float t, const Color3 &c)
    {
        return Color3(t * c.x(), t * c.y(), t * c.z());
    }

    inline Color3 operator+(const Color3 &u, const Color3 &v)
    {
        return Color3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
    }

    inline Color3 operator*(const Color3 &u, const Color3 &v)
    {
        return Color3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
    }

    inline Color3 operator-(const Color3 &u, const Color3 &v)
    {
        return Color3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
    }

    inline Vec3 operator-(const Point3 &u, const Point3 &v)
    {
        return Vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
    }

    inline Color3 operator/(Color3 c, float t)
    {
        return Color3(c.x() / t, c.y() / t, c.z() / t);
    }
} // namespace Raytracing