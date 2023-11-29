#pragma once

#include <fstream>
#include "Utils.h"
#include "Interval.h"

struct Vec3;
Vec3 unit_vector(Vec3 v);
double dot(const Vec3 &u, const Vec3 &v);

struct Vec3 { // just POD type
    double x, y, z;
    Vec3 operator-() const;
    double operator[](int i) const;
    double& operator[](int i);

    Vec3& operator+=(const Vec3 &v);
    Vec3& operator*=(double t);
    Vec3& operator/=(double t);

    [[nodiscard]] double length() const;
    [[nodiscard]] double length_squared() const;

    [[nodiscard]] static Vec3 random(Interval range = {0,1});

    [[nodiscard]] static inline Vec3 random_in_unit_sphere() {
        while (true) {
            Vec3 p = random({-1, 1});
            if (p.length_squared() < 1) {
                return p;
            }
        }
        // see ./assets/random_samples_in_unit_square for diagram of rejection method
    }

    [[nodiscard]] static inline Vec3 random_unit_vector() {
        /// return random vector on the surface of the unit sphere
        return unit_vector(random_in_unit_sphere());
    }

    [[nodiscard]] static Vec3 random_on_hemisphere(const Vec3& normal);
    [[nodiscard]] bool is_near_zero() const;
};

using Point3 = Vec3; // useful for geometric clarity in the code

// Vector Utility Functions
std::ostream& operator<<(std::ostream& out, const Vec3 &v);
Vec3 operator+(const Vec3 &u, const Vec3 &v);
Vec3 operator-(const Vec3 &u, const Vec3 &v);
Vec3 operator*(const Vec3 &u, const Vec3 &v);
Vec3 operator*(double t, const Vec3 &v);
Vec3 operator*(const Vec3 &v, double t);
Vec3 operator/(Vec3 v, double t);

Vec3 cross(const Vec3 &u, const Vec3 &v);

Vec3 reflection_ray(const Vec3& v, const Vec3& normal_as_unit_vector);
Vec3 refraction_ray(const Vec3& incident_ray_direction, const Vec3& surface_normal, double etai_over_etat);