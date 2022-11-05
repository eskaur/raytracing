#include <Render.h>

#include <iostream>

namespace Raytracing
{
    void render(Image &image, std::function<float(size_t, size_t, Color)> renderFunc)
    {
        for(size_t i = 0; i < image.height(); ++i)
        {
            std::cout << "Rendering line: " << i << std::endl;
            for(size_t j = 0; j < image.width(); ++j)
            {
                image(i, j, Color::Red) = renderFunc(i, j, Color::Red);
                image(i, j, Color::Green) = renderFunc(i, j, Color::Green);
                image(i, j, Color::Blue) = renderFunc(i, j, Color::Blue);
            }
        }
        std::cout << "\nDone.\n";
    }
} // namespace Raytracing