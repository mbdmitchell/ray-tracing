#pragma once

#include "Colour.h"
#include "HittableEntities/ListOfHittables.h"
#include "Ray.h"
#include "Vec3.h"
#include "material/Material.h"

Colour ray_colour(const Ray& ray, const ListOfHittables& world, int depth);