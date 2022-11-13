#include <Image.h>
#include <Object.h>
#include <Ray.h>
#include <Render.h>
#include <Scene.h>
#include <Vec.h>

int main()
{
    using namespace Raytracing;

    // Scene
    Scene scene;
    scene.addObject(std::make_unique<Sphere>(Point3(0.1, 0, -1), 0.5));
    scene.addObject(std::make_unique<Sphere>(Point3(-1, -0.25, -1.5), 0.25));
    scene.addObject(std::make_unique<Sphere>(Point3(0, -50.5, -1), 50));

    // Image
    const auto aspectRatio = 16.0F / 9.0F;
    const int height = 200;
    const int width = height * aspectRatio;
    auto image = Image(height, width);

    // Camera
    const float viewportHeight = 2.0F;
    const float viewportWidth = aspectRatio * viewportHeight;
    const float focalLength = 1.0F;
    auto renderer = Renderer(viewportHeight, viewportWidth, focalLength);

    // Render
    renderer.render(image, scene);
    image.save("image.ppm");
}