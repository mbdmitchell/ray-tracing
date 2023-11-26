#pragma once

#include "format"
#include "gsl/gsl"
#include "Colour.h"
#include "Vec3.h"
#include "Ray.h"
#include "Viewport.h"
#include "RayUtils.h"
#include "ImageDimensions.h"

void render(std::ostream& os, const ImageDimensions& dim, const Viewport& viewport, const Camera& camera);