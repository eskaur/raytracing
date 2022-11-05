#pragma once

#include <Image.h>

#include <functional>

namespace Raytracing
{
    void render(Image &image, std::function<float(size_t, size_t, Color)>);
}