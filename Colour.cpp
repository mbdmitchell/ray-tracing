#include "Colour.h"

int scaleTo255(double normalizedValue) {
    const double scalingFactor = 255.999;
    return static_cast<int>(scalingFactor * normalizedValue);
}

void writeColor(std::ostream &out, Colour pixelColour) {

    const double normalizedRed = pixelColour.x;
    const double normalizedBlue = pixelColour.y;
    const double normalizedGreen = pixelColour.z;

    const int r = static_cast<int>(scaleTo255(normalizedRed));
    const int g = static_cast<int>(scaleTo255(normalizedBlue));
    const int b = static_cast<int>(scaleTo255(normalizedGreen));

    out << std::format("{} {} {}\n", r, g, b);
}