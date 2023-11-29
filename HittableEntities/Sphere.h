#pragma once

#include <utility>

#include "../Vec3.h"
#include "HittableEntity.h"
#include "../material/Material.h"

class Sphere : public HittableEntity {
    double m_radius;
    Point3 m_center;
    std::shared_ptr<Material> m_material;

    [[nodiscard]] bool is_hit(const Ray& ray, Interval t_range) const override;
    void update_hit_record(HitRecord& record, const Ray& ray, std::optional<double> t) const;

    [[nodiscard]] QuadraticCoefficients calc_quadratic_coefficients(const Ray& ray) const;

public:
    template<typename T>
    Sphere(double radius, const Point3 &center, T material) : m_radius{radius}, m_center{center} {
        static_assert(std::is_base_of<Material, T>::value, "T must be derived from Material");

        if (m_radius <= 0) {
            throw std::invalid_argument("radius must be >0");
        }

        m_material = std::make_unique<T>(material);
    }

    [[deprecated("Refactor to use is_hit() and update_hit_record()")]] [[nodiscard]]
    bool is_hit_and_update_hit_record(const Ray& ray, Interval t_range, HitRecord& hit_record) const override;

    [[nodiscard]] double radius() const;
    [[nodiscard]] const Point3& center() const;
};