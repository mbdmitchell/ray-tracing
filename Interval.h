#pragma once

#include <numeric>

class Interval {
    double m_min = -std::numeric_limits<double>::infinity();
    double m_max = +std::numeric_limits<double>::infinity();
public:
    Interval() = default;
    Interval(double min, double max) : m_min(min), m_max(max) {}

    [[nodiscard]] bool contains(double x) const;
    [[nodiscard]] bool surrounds(double x) const;

    [[nodiscard]] double min() const {return m_min;}
    [[nodiscard]] double max() const {return m_max;}

    static const Interval empty;
    static const Interval universe;
};
