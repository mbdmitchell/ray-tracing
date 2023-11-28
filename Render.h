#pragma once

#include "format"
#include "gsl/gsl"
#include "Viewport.h"
#include "RayUtils.h"

void render(std::ostream& os, const ImageDimensions& dim, const Viewport& viewport, const Camera& camera, const ListOfHittables& world);