#pragma once

#include "../Ray.h"
#include "../Vec3.h"
#include "../Interval.h"
#include "../Colour.h"
#include "../HittableEntities/HitRecord.h"

struct HitRecord;

/*
For our program the material needs to do two things:
- Produce a scattered ray (or say it absorbed the incident ray).
- If scattered, say how much the ray should be attenuated.
*/

class Material {
public:
    virtual ~Material() = default;
    [[nodiscard]] virtual bool scatter(const Ray& ray_in, const HitRecord& record, Colour& attenuation, Ray& scattered) const = 0; // TODO: always true? refactor to void
};

class Lambertian : public Material {
    Colour albedo;
public:
    explicit Lambertian(const Colour& albedo);
    [[nodiscard]] bool scatter(const Ray& ray_in, const HitRecord& record, Colour& attenuation, Ray& scattered) const override;
};

class Metal : public Material {
    Colour albedo;
    double fuzz_factor;
public:
    Metal(const Colour& albedo, double fuzz_factor);
    [[nodiscard]] bool scatter(const Ray& ray_in, const HitRecord& record, Colour& attenuation, Ray& scattered) const override;
};

class Dielectric : public Material {
    /// Material always refracts
    double refraction_index;
public:
    Dielectric(double refraction_index) : refraction_index{refraction_index} { }
    [[nodiscard]] bool scatter(const Ray& ray_in, const HitRecord& record, Colour& attenuation, Ray& scattered) const override;
};