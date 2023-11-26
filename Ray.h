#pragma once

#include "Vec3.h"
#include "Camera.h"

struct Ray {
    Point3 origin;
    Vec3 direction;
    [[nodiscard]] inline Point3 at(double time) const;
};

