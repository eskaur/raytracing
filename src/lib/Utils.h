#pragma once

#include <random>

namespace Raytracing
{
    inline double random()
    {
        static thread_local std::uniform_real_distribution<float> distribution(0.0F, 1.0F);
        static thread_local std::mt19937 generator;
        return distribution(generator);
    }

    inline float random(float min, float max)
    {
        // Returns a random real in [min,max).
        return min + (max - min) * random();
    }

    inline Point3 randomPoint(float min, float max)
    {
        return Point3(random(min, max), random(min, max), random(min, max));
    }

    inline Point3 random_point_in_unit_sphere()
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

} // namespace Raytracing