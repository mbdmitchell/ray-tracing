#pragma once

#include "Vec3.h"

struct Ray {
    Point3 origin;
    Vec3 direction;
    [[nodiscard]] Point3 at(double time) const;
};

