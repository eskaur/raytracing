#include <Image.h>
#include <Render.h>

#include <iostream>

int main()
{
    auto image = Raytracing::Image(255, 255);

    auto renderFunc = [&image](size_t i, size_t j, Raytracing::Color color) {
        switch(color)
        {
            case Raytracing::Color::Red: return float(j) / (image.width() - 1);
            case Raytracing::Color::Green: return float(i) / (image.height() - 1);
            case Raytracing::Color::Blue: return 0.25F;
            default: throw std::runtime_error("Unknown color");
        }
    };

    Raytracing::render(image, renderFunc);
    image.save("image.ppm");
}