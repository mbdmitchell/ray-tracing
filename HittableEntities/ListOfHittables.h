#pragma once

#include "HittableEntity.h"
#include <memory>
#include <utility>
#include <vector>

class ListOfHittables : public HittableEntity {
    std::vector<std::shared_ptr<HittableEntity>> entities;
    [[nodiscard]] bool is_hit(const Ray& ray, Interval t_range) const override;
public:
    ListOfHittables() = default;

    template<typename... Args>
    ListOfHittables(Args&&... args) {
        (add(std::forward<Args>(args)), ...);
    }

    template<typename T>
    void add(T&& entity) {
        static_assert(std::is_base_of<HittableEntity, T>::value, "T must be derived from HittableEntity");
        entities.push_back(std::make_shared<T>(std::forward<T>(entity)));
    }

    void clear();
    [[deprecated]] bool is_hit_and_update_hit_record(const Ray& ray, Interval t_range, HitRecord& hit_record) const override;
};
