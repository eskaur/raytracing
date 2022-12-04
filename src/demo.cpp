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
        std::make_unique<Sphere>(Point3(0.1, -0.2, -1.4), 0.3, std::make_unique<Metal>(Color3(0.5, 0.0, 0.0), 0.75)));
    //Green sphere
    scene.addObject(std::make_unique<Sphere>(
        Point3(-0.65, -0.25, -1.3), 0.25, std::make_unique<Lambertian>(Color3(0.0, 0.5, 0.0))));
    // Blue shiny sphere
    scene.addObject(
        std::make_unique<Sphere>(Point3(0.2, -0.4, -0.8), 0.10, std::make_unique<Lambertian>(Color3(0.1, 0.1, 0.9))));
    // Metallic spheres
    scene.addObject(
        std::make_unique<Sphere>(Point3(-0.3, -0.4, -1.0), 0.1, std::make_unique<Metal>(Color3(1, 0.7, 0.1))));
    scene.addObject(
        std::make_unique<Sphere>(Point3(0.6, -0.3, -1.1), 0.2, std::make_unique<Metal>(Color3(1, 0.7, 0.1))));
    // Floor
    scene.addObject(std::make_unique<XZRect>(
        Point3(0.0, -0.5, 0.0), 1000, 1000, std::make_unique<Lambertian>(Color3(0.2, 0.2, 0.5))));
    // Left wall
    scene.addObject(
        std::make_unique<YZRect>(Point3(-1.0, 0.0, 0.0), 1, 1000, std::make_unique<Metal>(Color3(0.5, 0.5, 0.5), 0.2)));
    // Right wall
    scene.addObject(
        std::make_unique<YZRect>(Point3(1.0, 0.0, 0.0), 1, 1000, std::make_unique<Metal>(Color3(0.2, 0.2, 0.2), 0.2)));
    // Back wall
    scene.addObject(
        std::make_unique<XYRect>(Point3(0.0, 0.0, -2.0), 10, 1, std::make_unique<Lambertian>(Color3(0.2, 0.2, 0.2))));
    // Ceiling panels
    scene.addObject(
        std::make_unique<XZRect>(Point3(0.0, 0.5, -1.9), 2, 0.3, std::make_unique<Lambertian>(Color3(0.2, 0.2, 0.2))));
    scene.addObject(
        std::make_unique<XZRect>(Point3(0.0, 0.5, -1.4), 2, 0.3, std::make_unique<Lambertian>(Color3(0.2, 0.2, 0.2))));
    scene.addObject(
        std::make_unique<XZRect>(Point3(0.0, 0.5, -0.9), 2, 0.3, std::make_unique<Lambertian>(Color3(0.2, 0.2, 0.2))));
    scene.addObject(
        std::make_unique<XZRect>(Point3(0.0, 0.5, -0.4), 2, 0.3, std::make_unique<Lambertian>(Color3(0.2, 0.2, 0.2))));
    // Box
    scene.addObject(std::make_unique<Box>(
        Point3(-0.8, -0.45, -1.0), Vec3(0.10, 0.10, 0.10), std::make_unique<Lambertian>(Color3(0.7, 0.0, 0.0))));

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