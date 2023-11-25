#pragma once

#include "Vec3.h"

struct Ray {
    Point3 origin;
    Vec3 direction;
    Ray() = default;
    [[nodiscard]] inline Point3 at(double time) const;
};

