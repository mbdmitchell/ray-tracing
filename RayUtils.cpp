#include "RayUtils.h"


Colour ray_colour(const Ray &ray, const ListOfHittables& world, int depth) {

    HitRecord record;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0) {
        return {0,0,0};
    }

    if (world.is_hit_and_update_hit_record(ray, {0.001, std::numeric_limits<double>::infinity()}, record)) {
        Ray scattered{};
        Colour attenuation{};
        if (record.material->scatter(ray, record, attenuation, scattered)) {
            return attenuation * ray_colour(scattered, world, depth - 1);
        }
        return {0,0,0};
    }

    const Vec3 unit_direction = unit_vector(ray.direction);
    const double lerp_factor = 0.5 * (unit_direction.y + 1.0); // scales the range of values from -1 to 1 to a range of 0 to 1

    const Colour startValue = {1, 1, 1};
    const Colour endValue = {0.5,0.7,1};

    return ((1-lerp_factor) * startValue) + (lerp_factor * endValue); // return a “linear interpolation” / "lerp"
}
