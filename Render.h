#pragma once

#include "format"
#include "gsl/gsl"
#include "Viewport.h"
#include "RayUtils.h"
#include "Utils.h"
#include "Countdown.h"

void render(std::ostream& os, const ImageDimensions& dim, const Viewport& viewport, const Camera& camera, const ListOfHittables& world, int samples_per_pixel);

Ray generate_random_ray_from_position(gsl::index i, gsl::index j, const Viewport& viewport, const Camera& camera);
