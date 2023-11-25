#include "Ray.h"

Point3 Ray::at(double time) const {
    return origin + (time * direction);
}
