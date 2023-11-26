#include "RayUtils.h"

std::optional<double> smallest_t_that_hits(const Sphere& sphere, const Ray& ray) {
    /// for ray P(t), ray hits sphere when t = (-b ± sqrt(b^2 - 4ac)) / 2a  (*)

    const Vec3 center_to_origin = ray.origin - sphere.center();
    const double a = dot(ray.direction, ray.direction);
    const double b = 2.0 * dot(center_to_origin, ray.direction);
    const double c = dot(center_to_origin, center_to_origin) - sphere.radius()*sphere.radius();
    const double discriminant = b*b - 4*a*c;

    if (discriminant < 0) {
        return std::nullopt;
    }
    else {
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }

    // (*) DERIVATION
    // (P-C) • (P-C) = r^2, where c is sphere centre and p is some point
    // ⇒ ((A+tb)-C) • ((A+tb)-C) = r^2
    // ⇒ (b•b)t^2 + 2(b•(A-C))t + (A-C)•(A-C) - r^2 = 0
}

Colour ray_colour(const Ray &ray) {

    const Sphere sphere = {0.5, Point3(0, 0, -1)}; // test sphere
    std::optional<double> t = smallest_t_that_hits(sphere, ray);

    if (t.has_value()) {
        Vec3 normal = unit_vector(ray.at(t.value()) - Vec3{0, 0, -1});
        return 0.5 * Colour{normal.x + 1, normal.y + 1, normal.z + 1};
    }

    const Vec3 unit_direction = unit_vector(ray.direction);
    const double lerp_factor = 0.5 * (unit_direction.y + 1.0); // scales the range of values from -1 to 1 to a range of 0 to 1

    const Colour startValue = {1, 1, 1};
    const Colour endValue = {0.5,0.7,1};

    return ((1-lerp_factor) * startValue) + (lerp_factor * endValue); // return a “linear interpolation” / "lerp"
}
