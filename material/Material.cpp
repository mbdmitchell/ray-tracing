#include "Material.h"

bool Lambertian::scatter(const Ray &ray_in, const HitRecord &record, Colour &attenuation, Ray &scattered) const {

    const Vec3 scatter_direction = [&]() -> Vec3 {
        Vec3 s = record.surface_normal + Vec3::random_unit_vector();
        // Catch degenerate scatter direction
        if (s.is_near_zero()) { // (*)
            s = record.surface_normal;
        }
        return s;
    }();

    // update
    attenuation = albedo;
    scattered = Ray{record.point, scatter_direction};

    return true;

    /*
     (*) "If the random unit vector we generate is exactly opposite the normal vector, the
     two will sum to zero, which will result in a zero scatter direction vector. This leads
     to bad scenarios later on (infinities and NaNs), so we need to intercept the condition
     before we pass it on."

     "For the Lambertian (diffuse) case we already have, it can either always scatter and
     attenuate by its reflectance 𝑅, or it can sometimes scatter (with probabilty 1−𝑅)
     with no attenuation (where a ray that isn't scattered is just absorbed into the
     material). It could also be a mixture of both those strategies." - raytracing.github.io
     */
}

Lambertian::Lambertian(const Colour &albedo) : albedo{albedo} {}

bool Metal::scatter(const Ray &ray_in, const HitRecord &record, Colour &attenuation, Ray &scattered) const {
    const Vec3 reflected = reflect(unit_vector(ray_in.direction), record.surface_normal);
    scattered = Ray{record.point, reflected + fuzz_factor * Vec3::random_unit_vector()};
    attenuation = albedo;

    // For big spheres or grazing rays, we may scatter below the surface. We can just have the surface absorb those.
    return dot(scattered.direction, record.surface_normal) > 0;
}

Metal::Metal(const Colour &albedo, double fuzz)
    : albedo{albedo}, fuzz_factor{std::clamp(fuzz, 0.0, 1.0)} {}
