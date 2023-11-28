#include "RayUtils.h"

Colour ray_colour(const Ray &ray, const ListOfHittables& world) {

    HitRecord record{};

    if (world.is_hit_and_update_hit_record(ray, {0,std::numeric_limits<double>::infinity()}, record)) {
        return 0.5 * (record.surface_normal + Colour{1,1,1});
    }

    const Vec3 unit_direction = unit_vector(ray.direction);
    const double lerp_factor = 0.5 * (unit_direction.y + 1.0); // scales the range of values from -1 to 1 to a range of 0 to 1

    const Colour startValue = {1, 1, 1};
    const Colour endValue = {0.5,0.7,1};

    return ((1-lerp_factor) * startValue) + (lerp_factor * endValue); // return a “linear interpolation” / "lerp"
}
