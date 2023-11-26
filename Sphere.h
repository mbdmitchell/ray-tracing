#pragma once

#include "Vec3.h"

class Sphere {
    double m_radius;
    Point3 m_center;
public:
    Sphere(double radius, const Point3& center);
    [[nodiscard]] double radius() const;
    [[nodiscard]] const Point3& center() const;
};