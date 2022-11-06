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
    scene.addObject(std::make_unique<Sphere>(Point3(-0.3, 0, -1.5), 0.5));
    scene.addObject(std::make_unique<Sphere>(Point3(0.3, 0, -1), 0.5));
    scene.addObject(std::make_unique<Sphere>(Point3(0, -501, -1), 500));

    // Image
    const auto aspectRatio = 16.0F / 9.0F;
    const int width = 600;
    const int height = width / aspectRatio;
    auto image = Image(height, width);

    // Camera
    const float viewportHeight = 2.0F;
    const float viewportWidth = aspectRatio * viewportHeight;
    const float focalLength = 1.0F;
    auto renderer = Renderer(viewportHeight, viewportWidth, focalLength);

    // Render
    auto renderFunc = [&scene](const Ray &ray) { return scene.shootRay(ray); };
    renderer.render(image, renderFunc);
    image.save("image.ppm");
}