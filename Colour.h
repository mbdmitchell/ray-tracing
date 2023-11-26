#pragma once

#include "Vec3.h"
#include <iostream>
#include "format"

using Colour = Vec3;

int scale_to_255(double normalizedValue);
void write_color(std::ostream &out, Colour pixelColour);
