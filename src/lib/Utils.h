#pragma once

#include <random>

namespace Raytracing
{
    inline double random()
    {
        static std::uniform_real_distribution<float> distribution(0.0F, 1.0F);
        static std::mt19937 generator;
        return distribution(generator);
    }

    inline float random(float min, float max)
    {
        // Returns a random real in [min,max).
        return min + (max - min) * random();
    }

} // namespace Raytracing