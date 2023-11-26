#include "Sphere.h"

Sphere::Sphere(double radius, const Point3 &center) : m_radius{radius}, m_center{center} {
    if (m_radius <= 0) {
        throw std::invalid_argument("radius must be >0");
    }
}

double Sphere::radius() const { return m_radius; }

const Point3 &Sphere::center() const { return m_center; }
