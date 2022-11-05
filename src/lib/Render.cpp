#include <Render.h>

#include <iostream>

namespace Raytracing
{
    void render(Image &image, std::function<Vec3(size_t, size_t)> renderFunc)
    {
        for(size_t i = 0; i < image.height(); ++i)
        {
            std::cout << "Rendering line: " << i << std::endl;
            for(size_t j = 0; j < image.width(); ++j)
            {
                image(i, j) = renderFunc(i, j);
            }
        }
        std::cout << "\nDone.\n";
    }
} // namespace Raytracing