#pragma once

#include <numbers>
#include <random>

namespace utils {
    inline double degrees_to_radians(double degrees) {
        return degrees * std::numbers::pi / 180.0;
    }

    // Returns a random real in [0, 1)
    inline double random_double() {
        static std::mt19937 generator(std::random_device{}());
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        return distribution(generator);
    }

// Returns a random real in [min, max)
    inline double random_double(double min, double max) {
        static std::mt19937 generator(std::random_device{}());
        std::uniform_real_distribution<double> distribution(min, max);
        return distribution(generator);
    }
}