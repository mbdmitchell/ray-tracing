#pragma once

#include "Colour.h"
#include "HittableEntities/ListOfHittables.h"
#include "Ray.h"

Colour ray_colour(const Ray& ray, const ListOfHittables& world);