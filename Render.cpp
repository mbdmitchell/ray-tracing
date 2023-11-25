#include "Render.h"

void render(const ImageDimensions &dim, std::ostream &os) {
    /// Write PPM image file to ostream

    // Render header
    os << std::format("P3\n{} {}\n255\n", dim.width, dim.height);

    // TODO: Logger scanLinesRemaining = dim.height;

    for (gsl::index j = 0; j < dim.height; ++j) {

        // scanLinesRemaining.print();

        for (gsl::index i = 0; i < dim.width; ++i) {

            // test values
            const Colour pixel_colour = {  gsl::narrow_cast<double>(i) / gsl::narrow_cast<double>(dim.width - 1)  // R
                    , gsl::narrow_cast<double>(j) / gsl::narrow_cast<double>(dim.height - 1) // G
                    , 0};                                                                    // B

            write_color(os, pixel_colour);
        }

        // --scanLinesRemaining;
    }
}
