#ifndef COLOR_H
#define COLOR_H

#include "Vector3.h"

using Color = Vector3;

void writeColor(std::ostream &out, const Color &pixelColor)
{
    auto red = pixelColor.x();
    auto green = pixelColor.y();
    auto blue = pixelColor.z();

    // Translate the [0,1] component values to the byte range [0,255].
    int redByte = int(255.999 * red);
    int greenByte = int(255.999 * green);
    int blueByte = int(255.999 * blue);

    // Write out the pixel color components.
    out << redByte << ' ' << greenByte << ' ' << blueByte << '\n';
}

#endif
