#pragma once

#include <cassert>
#include "../Ray.h"
#include <iostream>
#include <iomanip>
#include "../format"

struct HitRecord {
    Point3 point;
    Vec3 surface_normal;
    double t;
    bool is_front_face;

    void set_face_and_surface_normal(const Ray& ray, const Vec3& outward_normal);
};
