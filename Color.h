#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "Vector3.h"

using Color = Vector3;

void write_color(std::ostream& out, const Color& pixel_color) {
    auto red = pixel_color.x();
    auto green = pixel_color.y();
    auto blue = pixel_color.z();

    // Translate the [0,1] component values to the byte range [0,255].
    int red_byte = int(255.999 * red);
    int green_byte = int(255.999 * green);
    int blue_byte = int(255.999 * blue);

    // Write out the pixel color components.
    out << red_byte << ' ' << green_byte << ' ' << blue_byte << '\n';
}

#endif
