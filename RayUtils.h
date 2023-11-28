#pragma once

#include "Colour.h"
#include "HittableEntities/ListOfHittables.h"
#include "Ray.h"
#include "Vec3.h"

Colour ray_colour(const Ray& ray, const ListOfHittables& world, int depth);