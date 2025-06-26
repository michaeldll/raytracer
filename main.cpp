#include <iostream>
#include "Color.h"
#include "Vector3.h"
#include "Ray.h"

double hitSphere(const Vector3 &center, double radius, const Ray &ray)
{
    Vector3 fromCenter = center - ray.origin();
    auto a = dot(ray.direction(), ray.direction());
    auto b = -2.0 * dot(ray.direction(), fromCenter);
    auto c = dot(fromCenter, fromCenter) - radius * radius;
    auto discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-b - std::sqrt(discriminant)) / (2.0 * a);
    }
}

Vector3 getSphereNormal(const double t, const Vector3 &center, const Ray &ray)
{
    // normal is normalized vector from sphere center to hit point.
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

Color getRayColor(const Ray &ray)
{
    const auto CENTER = Vector3(0, 0, -1);
    const auto RADIUS = 0.5;
    auto t = hitSphere(CENTER, RADIUS, ray);
    if (t > 0.0)
    // Hit sphere
    {
        // Get normal
        const auto normal = getSphereNormal(t, CENTER, ray);
        // Map it to [0, 1]
        const Vector3 *mapped = new Vector3((normal.x() + 1) * 0.5, (normal.y() + 1) * 0.5, (normal.z() + 1) * 0.5);
        // Debug color
        const auto result = Color(mapped->x(), mapped->y(), mapped->z());
        delete mapped;
        return result;
    }
    else
    // Hit nothing
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

            Color pixelColor = getRayColor(ray);

            write_color(std::cout, pixelColor);
        }
    }

    std::clog << "\rDone.                 \n";
}
