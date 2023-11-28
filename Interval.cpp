#include "Interval.h"

bool Interval::contains(double x) const {
    return min() <= x && x <= max();
}

bool Interval::surrounds(double x) const {
    return min() < x && x < max();
}

const Interval Interval::empty{+std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity()};
const Interval Interval::universe{};