#pragma once

#include <numbers>
#include <random>
#include "Interval.h"

namespace utils {
    inline double degrees_to_radians(double degrees) {
        return degrees * std::numbers::pi / 180.0;
    }

    inline double random_double(Interval range = {0,1}) {
        static std::mt19937 generator(std::random_device{}());
        std::uniform_real_distribution<double> distribution(range.min(), range.max());
        return distribution(generator);
    }
}