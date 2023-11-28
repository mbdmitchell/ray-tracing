#pragma once

#include "../Vec3.h"
#include "HittableEntity.h"

class Sphere : public HittableEntity {
    double m_radius;
    Point3 m_center;

    [[nodiscard]] bool is_hit(const Ray& ray, Interval t_range) const override;
    void update_hit_record(HitRecord& record, const Ray& ray, std::optional<double> t) const;

    [[nodiscard]] QuadraticCoefficients calc_quadratic_coefficients(const Ray& ray) const;

public:
    [[deprecated("use is_hit() and update_hit_record()")]] [[nodiscard]] bool is_hit_and_update_hit_record(const Ray& ray, Interval t_range, HitRecord& hit_record) const override;
    Sphere(double radius, const Point3& center);
    [[nodiscard]] double radius() const;
    [[nodiscard]] const Point3& center() const;
};