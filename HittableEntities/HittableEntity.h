#pragma once

#include "HitRecord.h"
#include "../Interval.h"

class HittableEntity {
protected:
    struct QuadraticCoefficients {
        double a, half_b, sqrt_of_discriminant;
    };
public:
    virtual ~HittableEntity() = default;
    [[nodiscard]] virtual bool is_hit(const Ray &ray, Interval t_range) const = 0;
    static std::optional<double> nearest_root_in_range(Interval t_range, double a, double half_b, double sqrt_of_discriminant);

    [[deprecated]] virtual bool is_hit_and_update_hit_record(const Ray& ray, Interval t, HitRecord& hit_record) const = 0;
};
