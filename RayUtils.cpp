#include "RayUtils.h"

Colour ray_colour(const Ray &ray) {
    const Vec3 unit_direction = unit_vector(ray.direction);

    const double lerpFactor = 0.5 * (unit_direction.y + 1.0); // scales the range of values from -1 to 1 to a range of 0 to 1
    const double inverseLerpFactor = 1 - lerpFactor;

    const Colour startValue = {1, 1, 1};
    const Colour endValue = {0.5,0.7,1};

    return (inverseLerpFactor * startValue) + (lerpFactor * endValue); // <-- forms a  “linear interpolation” / "lerp"
}
