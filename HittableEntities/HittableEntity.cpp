#include "HittableEntity.h"

std::optional<double>
HittableEntity::nearest_root_in_range(Interval t_range, double a, double half_b, double sqrt_of_discriminant) {
    /// Where a,b,c are the coefficients of (b•b)t^2 + 2(b•(A-C))t + (A-C)•(A-C) - r^2 = 0

    const double root_1 = (-half_b - sqrt_of_discriminant) / a;
    const double root_2 = (-half_b + sqrt_of_discriminant) / a;

    if (t_range.surrounds(root_1)) return root_1;
    if (t_range.surrounds(root_2)) return root_2;
    return std::nullopt;
}
