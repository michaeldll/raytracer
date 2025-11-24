#include "common.h"

#include "Camera.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"

Color getBackgroundColor(const Ray &ray)
{
    Vector3 unitDirection = normalize(ray.direction());

    // Upwards
    auto alpha = 0.5 * (unitDirection.y() + 1.0);

    // Blue-ish
    Color startColor = Color(1.0, 1.0, 1.0);
    Color targetColor = Color(0.5, 0.7, 1.0);

    // Lerp
    return (1.0 - alpha) * startColor + alpha * targetColor;
}

Color getRayColor(const Ray &ray, const Hittable &scene)
{
    HitRecord record;
    if (scene.hit(ray, Interval(0, INFINITY_LIMIT), record))
    {
        return 0.5 * (record.normal + Color(1, 1, 1));
    }
    else
    {
        return getBackgroundColor(ray);
    }
}

int main()
{
    // Image settings
    const auto ASPECT_RATIO = 1.0;
    const int IMAGE_WIDTH = 400;

    // Camera
    Camera camera(ASPECT_RATIO, IMAGE_WIDTH);

    // World
    HittableList scene;
    scene.add(make_shared<Sphere>(Vector3(0, 0, -1), 0.5));
    scene.add(make_shared<Sphere>(Vector3(0, -100.5, -1.1), 100));

    // Render
    std::cout << "P3\n"
              << camera.getImageWidth() << ' ' << camera.getImageHeight() << "\n255\n";

    for (int y = 0; y < camera.getImageHeight(); y++)
    {
        std::clog << "\rRows remaining: " << (camera.getImageHeight() - y) << '\n'
                  << std::flush;
        for (int x = 0; x < camera.getImageWidth(); x++)
        {
            Ray ray = camera.getRay(x, y);
            Color pixelColor = getRayColor(ray, scene);
            writeColor(std::cout, pixelColor);
        }
    }

    std::clog << "\rDone.                 \n";
}
