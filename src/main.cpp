#include "common.h"

#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"

double hitSphere(const Vector3 &center, double radius, const Ray &ray)
{
    Vector3 fromCenter = center - ray.origin();
    // h=b−2=d⋅(C−Q)
    auto a = ray.direction().lengthSquared();
    auto h = dot(ray.direction(), fromCenter);
    auto c = fromCenter.lengthSquared() - radius * radius;
    auto discriminant = h * h - a * c;

    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (h - std::sqrt(discriminant)) / a;
    }
}

Vector3 getSphereNormal(const double t, const Vector3 &center, const Ray &ray)
{
    // Normal is normalized vector from sphere center to hit point.
    Vector3 fromCenter = ray.at(t) - center;
    return normalize(fromCenter);
}

Color getBackgroundColor(const Ray &ray)
{
    Vector3 unitDirection = normalize(ray.direction());
    auto alpha = 0.5 * (unitDirection.y() + 1.0);
    Color startColor = Color(1.0, 1.0, 1.0);
    Color targetColor = Color(0.5, 0.7, 1.0);
    // Lerp
    return (1.0 - alpha) * startColor + alpha * targetColor;
}

Color getRayColor(const Ray &ray, const Hittable &scene)
{
    HitRecord record;
    if (scene.hit(ray, 0, infinity, record))
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
    const int IMAGE_HEIGHT = int(IMAGE_WIDTH / ASPECT_RATIO);

    if (IMAGE_HEIGHT < 1)
    {
        throw std::runtime_error("IMAGE_HEIGHT must be at least 1");
    };

    // World
    HittableList scene;

    scene.add(make_shared<Sphere>(Vector3(0, 0, -1), 0.5));
    scene.add(make_shared<Sphere>(Vector3(0, -100.5, -1), 100));

    // Camera
    const auto FOCAL_LENGTH = 1.0;
    const auto VIEWPORT_HEIGHT = 2.0;
    const auto VIEWPORT_WIDTH = VIEWPORT_HEIGHT * (double(IMAGE_WIDTH) / IMAGE_HEIGHT);
    const auto CAMERA_CENTER = Vector3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    const auto VIEWPORT_U = Vector3(VIEWPORT_WIDTH, 0, 0);
    const auto VIEWPORT_V = Vector3(0, -VIEWPORT_WIDTH, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    const auto PIXEL_DELTA_U = VIEWPORT_U / IMAGE_WIDTH;
    const auto PIXEL_DELTA_V = VIEWPORT_V / IMAGE_HEIGHT;

    // Calculate the location of the upper left pixel.
    const auto VIEWPORT_UPPER_LEFT = CAMERA_CENTER - Vector3(0, 0, FOCAL_LENGTH) - VIEWPORT_U / 2 - VIEWPORT_V / 2;
    const auto PIXEL_START_POSITION = VIEWPORT_UPPER_LEFT + 0.5 * (PIXEL_DELTA_U + PIXEL_DELTA_V);

    // Render
    std::cout << "P3\n"
              << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

    for (int y = 0; y < IMAGE_HEIGHT; y++)
    {
        std::clog << "\rRows remaining: " << (IMAGE_HEIGHT - y) << '\n'
                  << std::flush;
        for (int x = 0; x < IMAGE_WIDTH; x++)
        {
            auto pixelCenter = PIXEL_START_POSITION + (x * PIXEL_DELTA_U) + (y * PIXEL_DELTA_V);
            auto rayDirection = pixelCenter - CAMERA_CENTER;
            Ray ray(CAMERA_CENTER, rayDirection);

            Color pixelColor = getRayColor(ray, scene);

            writeColor(std::cout, pixelColor);
        }
    }

    std::clog << "\rDone.                 \n";
}
