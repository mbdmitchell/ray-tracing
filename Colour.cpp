#include "Colour.h"

int scale_to_255(double normalizedValue) {
    /// interval [0,1] -> [0,255]
    const double scaling_factor = 255.999;
    return static_cast<int>(scaling_factor * normalizedValue);
}

void write_color(std::ostream &out, Colour pixelColour) {

    const double normalized_red = pixelColour.x;
    const double normalized_blue = pixelColour.y;
    const double normalized_green = pixelColour.z;

    const int r = static_cast<int>(scale_to_255(normalized_red));
    const int g = static_cast<int>(scale_to_255(normalized_blue));
    const int b = static_cast<int>(scale_to_255(normalized_green));

    out << std::format("{} {} {}\n", r, g, b);
}