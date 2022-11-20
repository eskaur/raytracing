#include <Image.h>
#include <Material.h>
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
    //Red sphere
    scene.addObject(
        std::make_unique<Sphere>(Point3(0.1, -0.1, -1), 0.4, std::make_unique<Lambertian>(Color3(0.5, 0.0, 0.0))));
    //Green sphere
    scene.addObject(std::make_unique<Sphere>(
        Point3(-0.65, -0.25, -1.1), 0.25, std::make_unique<Lambertian>(Color3(0.0, 0.5, 0.0))));
    // Metallic spheres
    scene.addObject(
        std::make_unique<Sphere>(Point3(-0.3, -0.4, -0.7), 0.1, std::make_unique<Metal>(Color3(1, 0.7, 0.1))));
    scene.addObject(
        std::make_unique<Sphere>(Point3(0.6, -0.3, -0.7), 0.2, std::make_unique<Metal>(Color3(1, 0.7, 0.1))));
    // Floor and wall
    scene.addObject(
        std::make_unique<Sphere>(Point3(0, -100.5, -1), 100, std::make_unique<Lambertian>(Color3(0.2, 0.2, 0.2))));
    scene.addObject(std::make_unique<Sphere>(Point3(-200, 0, -1), 199, std::make_unique<Metal>(Color3(0.5, 0.5, 0.9))));

    // Image
    const auto aspectRatio = 16.0F / 9.0F;
    const int height = 600;
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