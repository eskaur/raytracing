#include <Image.h>
#include <Render.h>
#include <Vec.h>

#include <iostream>

int main()
{
    auto image = Raytracing::Image(255, 255);

    auto renderFunc = [&image](size_t i, size_t j) {
        return Raytracing::Vec3(
            float(j) / (image.width() - 1),  //
            float(i) / (image.height() - 1), //
            0.25F                            //
        );
    };

    Raytracing::render(image, renderFunc);
    image.save("image.ppm");
}