#pragma once

#include "Vec3.h"

struct Camera {
    Vec3 center;
    double focal_length;
    [[nodiscard]] Vec3 getCenter() const { return center; }
    [[nodiscard]] double getFocalLength() const { return focal_length; }
};