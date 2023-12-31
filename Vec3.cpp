#include "Vec3.h"

Vec3 Vec3::operator-() const { return {-x, -y, -z}; }

double Vec3::operator[](int i) const {
    switch (i){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::invalid_argument("Out of bounds");
    }
}

double& Vec3::operator[](int i) {
    switch (i){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::invalid_argument("Out of bounds");
    }
}

Vec3 &Vec3::operator+=(const Vec3 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vec3 &Vec3::operator*=(double t) {
    x *= t;
    y *= t;
    z *= t;
    return *this;
}

Vec3 &Vec3::operator/=(double t) {
    return *this *= 1/t;
}

double Vec3::length() const {
    return sqrt(length_squared());
}

double Vec3::length_squared() const {
    return x*x + y*y + z*z;
}

bool Vec3::is_near_zero() const {
    /// Return true if the vector is close to zero in all dimensions.
    const double e = 1e-8;
    return abs(x) < e && abs(y) < e && abs(z) < e;
}

Vec3 Vec3::random(Interval range) {
    return {utils::random_double(range), utils::random_double(range), utils::random_double(range)};
}

Vec3 Vec3::random_on_hemisphere(const Vec3 &normal) {

    const Vec3 on_unit_sphere = random_unit_vector();
    const bool in_same_hemisphere_as_normal = dot(on_unit_sphere, normal) > 0.0;

    if (in_same_hemisphere_as_normal) {
        return on_unit_sphere;
    }
    else {
        return -on_unit_sphere;
    }

    /*We can take the dot product of the surface normal and our random vector
     * to determine if it's in the correct hemisphere. If the dot product is
     * positive, then the vector is in the correct hemisphere. If the dot
     * product is negative, then we need to invert the vector.*/
}

std::ostream &operator<<(std::ostream &out, const Vec3 &v) {
    out << v.x << ' ' << v.y << ' ' << v.z;
    return out;
}

Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return {u.x + v.x, u.y + v.y, u.z + v.z};
}

Vec3 operator-(const Vec3 &u, const Vec3 &v) {
    return {u.x - v.x, u.y - v.y, u.z - v.z};
}

Vec3 operator*(const Vec3 &u, const Vec3 &v) {
    return {u.x * v.x, u.y * v.y, u.z * v.z};
}

Vec3 operator*(double t, const Vec3 &v) {
    return {t*v.x, t*v.y, t*v.z};
}

Vec3 operator*(const Vec3 &v, double t) {
    return t * v;
}

Vec3 operator/(Vec3 v, double t) {
    return (1/t) * v;
}

double dot(const Vec3 &u, const Vec3 &v) {
    return u.x * v.x
           + u.y * v.y
           + u.z * v.z;
}

Vec3 cross(const Vec3 &u, const Vec3 &v) {
    return {u.y * v.z - u.z * v.y,
            u.z * v.x - u.x * v.z,
            u.x * v.y - u.y * v.x};
}

Vec3 unit_vector(Vec3 v) {
    return v / v.length();
}

Vec3 reflection_ray(const Vec3 &v, const Vec3 &normal_as_unit_vector) {
    return v - 2 * dot(v,normal_as_unit_vector) * normal_as_unit_vector;
}

Vec3 refraction_ray(const Vec3 &incident_ray_direction, const Vec3 &surface_normal, double etai_over_etat) {
    /// etai - refractive index of the medium where the incident ray is coming from
    /// etat - refractive index of the medium where the ray is entering

    const double cos_theta = std::min(dot(-incident_ray_direction, surface_normal), 1.0);
    const Vec3 ray_out_perpendicular = etai_over_etat * (incident_ray_direction + cos_theta * surface_normal);
    const Vec3 ray_out_parallel = -sqrt(abs(1.0 - ray_out_perpendicular.length_squared())) * surface_normal;

    return ray_out_perpendicular + ray_out_parallel;
}
