#include <iostream>
#include "Color.h"
#include "Vector3.h"
#include "Ray.h"

Color getRayColor(const Ray& ray) {
    return Color(0, 0, 0);
}

int main() {
    // Image Settings
    const int IMAGE_WIDTH = 512;
    const int IMAGE_HEIGHT = 512;

    // Render
    std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

    for (int y = 0; y < IMAGE_HEIGHT; y++) {
        std::clog << "\rScanlines remaining: " << (IMAGE_HEIGHT - y) << '\n' << std::flush;
        for (int x = 0; x < IMAGE_WIDTH; x++) {
            auto pixelColor = Color(double(x) / (IMAGE_WIDTH-1), double(y) / (IMAGE_HEIGHT-1), 0.0);
            write_color(std::cout, pixelColor);
        }
    }
    
    std::clog << "\rDone.                 \n";
}
