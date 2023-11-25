#pragma once

//#include <array>
#include <fstream>

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

double dot(const Vec3 &u, const Vec3 &v);
Vec3 cross(const Vec3 &u, const Vec3 &v);

Vec3 unitVector(Vec3 v);