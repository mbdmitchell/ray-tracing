#include "RayUtils.h"

std::optional<double> smallest_t_that_hits(const Sphere& sphere, const Ray& ray) {
    /// for ray P(t), ray hits sphere when t = (-b ± sqrt(b^2 - 4ac)) / 2a  (*)
    // Sub b = 2h and -> (-h ± sqrt(h^2 - 4ac)) / a

    const Vec3 center_to_origin = ray.origin - sphere.center();
    const double a = ray.direction.length_squared(); // vector dotted with itself is equal to the squared length of that vector
    const double half_b = dot(center_to_origin, ray.direction);
    const double c = center_to_origin.length_squared() - sphere.radius()*sphere.radius();
    const double discriminant = half_b*half_b - a*c;

    if (discriminant < 0) {
        return std::nullopt;
    }
    else {
        return (-half_b - sqrt(discriminant)) / a;
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
