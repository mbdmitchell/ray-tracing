#include "Render.h"

void render(std::ostream &os, const ImageDimensions &dim, const Viewport& viewport, const Camera& camera, const ListOfHittables& world) {
    /// Write PPM image file to ostream

    // Render header
    os << std::format("P3\n{} {}\n255\n", dim.width, dim.height);

    // TODO: Logger scanLinesRemaining = dim.height;

    for (gsl::index j = 0; j < dim.height; ++j) {

        // scanLinesRemaining.print();

        for (gsl::index i = 0; i < dim.width; ++i) {

            const Point3 pixel_center = viewport.pixel00()
                    + (gsl::narrow_cast<double>(i) * viewport.horizontal_pixel_delta())
                    + (gsl::narrow_cast<double>(j) * viewport.vertical_pixel_delta());
            const Ray r = {.origin = camera.center,
                           .direction = pixel_center - camera.center};
            const Colour pixel_colour = ray_colour(r, world);

            write_color(os, pixel_colour);
        }

        // --scanLinesRemaining;
    }
}
