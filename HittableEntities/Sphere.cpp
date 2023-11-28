#include "Sphere.h"

Sphere::Sphere(double radius, const Point3 &center) : m_radius{radius}, m_center{center} {
    if (m_radius <= 0) {
        throw std::invalid_argument("radius must be >0");
    }
}

double Sphere::radius() const { return m_radius; }

const Point3 &Sphere::center() const { return m_center; }

void Sphere::update_hit_record(HitRecord &record, const Ray &ray, std::optional<double> t) const {
    if (!t.has_value()) return;
    record.t = t.value();
    record.point = ray.at(record.t);

    const Vec3 outward_normal = (record.point - center()) / radius();
    record.set_face_and_surface_normal(ray, outward_normal);
}

[[deprecated]] bool Sphere::is_hit_and_update_hit_record(const Ray &ray, Interval t_range, HitRecord &hit_record) const {
    if (!is_hit(ray, t_range)) return false;

    const Vec3 center_to_origin = ray.origin - m_center;
    const double a = ray.direction.length_squared(); // vector dotted with itself is equal to the squared length of that vector
    const double half_b = dot(center_to_origin, ray.direction);
    const double c = center_to_origin.length_squared() - m_radius * m_radius;
    const double discriminant = half_b*half_b - a*c;

    const std::optional<double> nearest_valid_root = nearest_root_in_range(t_range, a, half_b, sqrt(discriminant));

    update_hit_record(hit_record, ray, nearest_valid_root);
    return nearest_valid_root.has_value();

}

HittableEntity::QuadraticCoefficients Sphere::calc_quadratic_coefficients(const Ray &ray) const {
    const Vec3 center_to_origin = ray.origin - m_center;
    const double a = ray.direction.length_squared(); // vector dotted with itself is equal to the squared length of that vector
    const double half_b = dot(center_to_origin, ray.direction);
    const double c = center_to_origin.length_squared() - m_radius * m_radius;
    return {a, half_b, c};
}

bool Sphere::is_hit(const Ray &ray, Interval t_range) const {
    /// For ray P(t), ray hits sphere when t = (-b ± sqrt(b^2 - 4ac)) / 2a  (*)
    /// Substitute b = 2h -> t = (-h ± sqrt(h^2 - 4ac)) / a

    const auto& [a, half_b, c] = calc_quadratic_coefficients(ray);
    const double discriminant = half_b*half_b - a*c;
    return discriminant >= 0 && nearest_root_in_range(t_range, a, half_b, sqrt(discriminant));

    // (*) DERIVATION
    // (P-C) • (P-C) = r^2, where c is sphere centre and p is some point
    // ⇒ ((A+tb)-C) • ((A+tb)-C) = r^2
    // ⇒ (b•b)t^2 + 2(b•(A-C))t + (A-C)•(A-C) - r^2 = 0
}
