#include <Image.h>
#include <Ray.h>
#include <Render.h>
#include <Vec.h>

#include <iostream>

Raytracing::Color3 rayColor(const Raytracing::Ray &r)
{
    const Raytracing::Vec3 unit_direction = Raytracing::unit_vector(r.direction());
    const float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0F - t) * Raytracing::Color3(1.0F, 0.5F, 0.5F) + t * Raytracing::Color3(0.5F, 0.7F, 1.0F);
}

int main()
{
    // Image
    const auto aspectRatio = 16.0F / 9.0F;
    const int width = 600;
    const int height = width / aspectRatio;
    auto image = Raytracing::Image(height, width);

    // Camera
    const float viewportHeight = 2.0F;
    const float viewportWidth = aspectRatio * viewportHeight;
    const float focalLength = 1.0F;

    // Render
    auto renderer = Raytracing::Renderer(viewportHeight, viewportWidth, focalLength);
    renderer.render(image, rayColor);
    image.save("image.ppm");
}