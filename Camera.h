#pragma once

#include "Vec3.h"
#include "Ray.h"
#include "Viewport.h"

class Camera {
    Point3 m_center;
    double m_focal_length;
public:
    Camera(Point3 center, double focal_length) : m_center{center}, m_focal_length{focal_length} { }
    auto center() const {return m_center; }
    auto focal_length() const {return m_focal_length; }

};