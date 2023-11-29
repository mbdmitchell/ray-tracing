#include "Colour.h"

int scale_to_255(double normalizedValue) {
    /// interval [0,1] -> [0,255]
    const double scaling_factor = 255.999;
    return static_cast<int>(scaling_factor * normalizedValue);
}

void write_color(std::ostream &out, Colour pixelColour) {

    const double normalized_red = pixelColour.x;
    const double normalized_green = pixelColour.y;
    const double normalized_blue = pixelColour.z;

    const int r = static_cast<int>((scale_to_255(linear_to_gamma(normalized_red))));
    const int g = static_cast<int>((scale_to_255(linear_to_gamma(normalized_green))));
    const int b = static_cast<int>((scale_to_255(linear_to_gamma(normalized_blue))));

    out << std::format("{} {} {}\n", r, g, b);
}

inline double linear_to_gamma(double linear_component) {
    return sqrt(linear_component);
}