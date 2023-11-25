#pragma once

#include "vec3.h"
#include <iostream>
#include "format"

using Colour = Vec3;

int scaleTo255(double normalizedValue);
void writeColor(std::ostream &out, Colour pixelColour);
