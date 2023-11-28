#include "Render.h"

void render(std::ostream &os, const ImageDimensions &dim, const Viewport& viewport, const Camera& camera, const ListOfHittables& world, int samples_per_pixel = 100) {
    /// Write PPM image file to ostream

    assert(samples_per_pixel > 0);

    Countdown scanLinesRemaining {dim.height};

    // Render header
    os << std::format("P3\n{} {}\n255\n", dim.width, dim.height);

    const double weight = 1.0 / samples_per_pixel;

    for (gsl::index j = 0; j < dim.height; ++j) {

        scanLinesRemaining.log();

        for (gsl::index i = 0; i < dim.width; ++i) {

            const Colour pixel_colour = std::invoke([&](){
                Colour col {0,0,0};

                for (gsl::index s = 0; s < samples_per_pixel; ++s) {
                    Ray ray = generate_random_ray_from_position(i,j, viewport, camera);
                    col += ray_colour(ray, world) * weight;
                }
                return col;
            });

            write_color(os, pixel_colour);
        }

        --scanLinesRemaining;
    }
}

Ray generate_random_ray_from_position(gsl::index i, gsl::index j, const Viewport &viewport, const Camera &camera) {
    /// Get a randomly sampled camera ray for the pixel at location i,j.

    auto pixel_sample_square = [&]() -> Vec3 {
        // Returns a random point in the square surrounding a pixel at the origin.
        auto px = -0.5 + utils::random_double();
        auto py = -0.5 + utils::random_double();
        return (px * viewport.horizontal_pixel_delta()) + (py * viewport.vertical_pixel_delta());
    };

    Point3 pixel_center = viewport.pixel00()
            + (gsl::narrow_cast<double>(i) * viewport.horizontal_pixel_delta())
            + (gsl::narrow_cast<double>(j) * viewport.vertical_pixel_delta());

    auto pixel_sample = pixel_center + pixel_sample_square();

    auto ray_origin = camera.center();
    auto ray_direction = pixel_sample - ray_origin;

    return Ray(ray_origin, ray_direction);
}

