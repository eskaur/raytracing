#pragma once

#include <Image.h>
#include <Vec.h>

#include <functional>

namespace Raytracing
{
    void render(Image &image, std::function<Vec3(size_t, size_t)>);
}