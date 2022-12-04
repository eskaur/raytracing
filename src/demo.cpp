#include <Camera.h>
#include <Material.h>
#include <Object.h>
#include <Scene.h>
#include <Utils.h>
#include <Vec.h>

namespace Raytracing
{
    namespace
    {
        // Materials
        const auto red = Color3(0.5, 0.0, 0.0);
        const auto green = Color3(0.0, 0.5, 0.0);
        const auto blue = Color3(0.1, 0.1, 0.9);
        const auto gold = Color3(1, 0.7, 0.1);
        const auto blueGray = Color3(0.2, 0.2, 0.5);
        const auto gray = Color3(0.4, 0.4, 0.4);
        const auto white = Color3(0.9, 0.9, 0.9);

        Scene manualScene()
        {
            Scene scene;
            //Red sphere
            scene.addObject(std::make_unique<Sphere>(Point3(0.1, 0.3, -1.4), 0.3, std::make_unique<Metal>(red, 0.75)));
            //Green sphere
            scene.addObject(
                std::make_unique<Sphere>(Point3(-0.65, 0.25, -1.3), 0.25, std::make_unique<Lambertian>(green)));
            // Blue shiny sphere
            scene.addObject(std::make_unique<Sphere>(Point3(0.2, 0.1, -0.8), 0.10, std::make_unique<Lambertian>(blue)));
            // Metallic spheres
            scene.addObject(std::make_unique<Sphere>(Point3(-0.3, 0.1, -1.0), 0.1, std::make_unique<Metal>(gold)));
            scene.addObject(std::make_unique<Sphere>(Point3(0.6, 0.2, -1.1), 0.2, std::make_unique<Metal>(gold)));
            // Floor
            scene.addObject(
                std::make_unique<XZRect>(Point3(0.0, 0.0, 0.0), 100, 100, std::make_unique<Lambertian>(blueGray)));
            // Left wall
            scene.addObject(
                std::make_unique<YZRect>(Point3(-1.0, 0.5, 0.0), 1, 1000, std::make_unique<Metal>(gray, 0.2)));
            // Right wall
            scene.addObject(
                std::make_unique<YZRect>(Point3(1.0, 0.5, 0.0), 1, 1000, std::make_unique<Metal>(gray, 0.2)));
            // Back wall
            scene.addObject(
                std::make_unique<XYRect>(Point3(0.0, 0.5, -2.0), 10, 1, std::make_unique<Lambertian>(gray)));
            // Ceiling panels
            scene.addObject(
                std::make_unique<XZRect>(Point3(0.0, 1.0, -1.9), 2, 0.3, std::make_unique<Lambertian>(gray)));
            scene.addObject(
                std::make_unique<XZRect>(Point3(0.0, 1.0, -1.4), 2, 0.3, std::make_unique<Lambertian>(gray)));
            scene.addObject(
                std::make_unique<XZRect>(Point3(0.0, 1.0, -0.9), 2, 0.3, std::make_unique<Lambertian>(gray)));
            scene.addObject(
                std::make_unique<XZRect>(Point3(0.0, 1.0, -0.4), 2, 0.3, std::make_unique<Lambertian>(gray)));
            // Box
            scene.addObject(std::make_unique<Box>(
                Point3(-0.8, 0.05, -1.0), Vec3(0.10, 0.10, 0.10), std::make_unique<Lambertian>(red)));

            return scene;
        }

        Scene randomizedScene()
        {
            Scene scene;

            // Floor
            const float floorLevel = -0.75F;
            scene.addObject(
                std::make_unique<XZRect>(Point3(0.0, floorLevel, 0.0), 100, 100, std::make_unique<Lambertian>(gray)));

            // Many small spheres
            const int n = 10;
            for(int a = -n; a < n; a++)
            {
                for(int b = -n; b < n; b++)
                {
                    const auto radius = 0.2F;
                    const auto materialChooser = random();
                    const auto centerPos = Point3(a + 0.8 * random(), floorLevel + radius, b + 0.8 * double());
                    std::unique_ptr<Material> material;
                    if(materialChooser < 0.8)
                    {
                        // Diffuse
                        const auto color = Color3(random(), random(), random());
                        material = std::make_unique<Lambertian>(color);
                    }
                    else
                    {
                        // Metal
                        const auto color = Color3(random(0.5F, 1.0F), random(0.5F, 1.0F), random(0.5F, 1.0F));
                        const auto roughness = random(0.0F, 0.5F);
                        material = std::make_unique<Metal>(color, roughness);
                    }

                    scene.addObject(std::make_unique<Sphere>(centerPos, radius, material->clone()));
                }
            }

            // Large spheres
            const auto largeRadius = 1.0F;
            scene.addObject(std::make_unique<Sphere>(
                Point3(0.1, floorLevel + largeRadius, -5.0), largeRadius, std::make_unique<Lambertian>(red)));
            scene.addObject(std::make_unique<Sphere>(
                Point3(1.5, floorLevel + largeRadius, -3.0), largeRadius, std::make_unique<Metal>(white, 0.05)));

            return scene;
        }

    } // namespace
} // namespace Raytracing

int main()
{
    using namespace Raytracing;

    // Scene
    const auto scene = manualScene();
    //const auto scene = randomizedScene();

    // Camera
    const auto aspectRatio = 16.0F / 9.0F;
    const int pixelHeight = 500;
    const float verticalFovDegrees = 70.0F;
    const auto cameraPos = Point3(0.1, 0.5, 0.0);
    const auto lookAt = Point3(-0.1, 0.2, -2.0);

    const auto camera = Camera(cameraPos, lookAt, aspectRatio, pixelHeight, verticalFovDegrees);

    // Render
    const auto image = camera.render(scene);
    image.save("image.ppm");
}