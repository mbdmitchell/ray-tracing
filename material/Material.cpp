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
    const Vec3 reflected = reflection_ray(unit_vector(ray_in.direction), record.surface_normal);
    scattered = Ray{record.point, reflected + fuzz_factor * Vec3::random_unit_vector()};
    attenuation = albedo;

    // For big spheres or grazing rays, we may scatter below the surface. We can just have the surface absorb those.
    return dot(scattered.direction, record.surface_normal) > 0;
}

Metal::Metal(const Colour &albedo, double fuzz)
    : albedo{albedo}, fuzz_factor{std::clamp(fuzz, 0.0, 1.0)} {}

bool Dielectric::scatter(const Ray &ray_in, const HitRecord &record, Colour &attenuation, Ray &scattered) const {

    const Vec3 unit_direction = unit_vector(ray_in.direction);
    const double cos_theta = std::min(dot(-unit_direction, record.surface_normal), 1.0);
    const double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    const double refraction_ratio = record.is_front_face ? (1.0/refraction_index) : refraction_index;
    const bool can_refract = refraction_ratio * sin_theta <= 1.0;

    const Vec3 direction = [&](){
        if (!can_refract || reflectance(cos_theta, refraction_ratio) > utils::random_double()) {
            return reflection_ray(unit_direction, record.surface_normal);
        }
        else {
            return refraction_ray(unit_direction, record.surface_normal, refraction_ratio);
        }
    }();

    attenuation = {1,1,1}; // Attenuation is always 1 — the surface absorbs nothing
    scattered = Ray{record.point, direction};

    return true;
}

double Dielectric::reflectance(double angle_of_incidence, double refractive_index) {

    // Use Schlick's approximation for reflectance.
    const double r0 = pow((1 - refractive_index)/(1 + refractive_index), 2);
    return r0 + (1 - r0) * pow((1-angle_of_incidence), 5);

    /* "reflectance" - often determines how shiny or reflective a surface appears.
     * Materials with high reflectance, like mirrors, reflect most incident light,
     * while materials with low reflectance, like matte surfaces, reflect less light,
     * appearing more diffuse.
     */
}
