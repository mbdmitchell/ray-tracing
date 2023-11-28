#include "HitRecord.h"

void HitRecord::set_face_and_surface_normal(const Ray &ray, const Vec3 &outward_normal) {
    /// outward_normal should be unit length

    constexpr double unit_length = 1.0;
    const double epsilon = 5e-16; // std::numeric_limits<double>::epsilon() is too small
    assert(std::abs(outward_normal.length() - unit_length) < epsilon);

    is_front_face = dot(ray.direction, outward_normal) < 0;
    surface_normal = is_front_face ? outward_normal : -outward_normal;

    /* If the ray and the normal face in the same direction, the ray is inside the object,
     * if the ray and the normal face in the opposite direction, then the ray is outside
     * the object. This can be determined by taking the dot product of the two vectors,
     * where if their dot is positive, the ray is inside the sphere.*/
}