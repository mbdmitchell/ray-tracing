#pragma once

#include <numbers>

namespace utils {
    inline double degrees_to_radians(double degrees) {
        return degrees * std::numbers::pi / 180.0;
    }
}