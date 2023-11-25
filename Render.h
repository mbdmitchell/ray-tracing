#pragma once

#include "format"
#include "gsl/gsl"
#include "Colour.h"
#include "Vec3.h"
#include "Ray.h"

struct ImageDimensions {
    size_t height;
    size_t width;
};


void render(const ImageDimensions& dim, std::ostream& os);