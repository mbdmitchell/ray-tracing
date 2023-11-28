#include "ListOfHittables.h"


void ListOfHittables::clear() {
    entities.clear();
}

bool ListOfHittables::is_hit_and_update_hit_record(const Ray &ray, Interval t_range, HitRecord &hit_record) const {

    HitRecord temp{};
    bool hit_anything = false;
    auto closest_so_far = t_range.max();

    for (const auto& entity : entities) {
        if (entity->is_hit_and_update_hit_record(ray, {t_range.min(), closest_so_far}, temp)) {
            hit_anything = true;
            closest_so_far = temp.t;
            hit_record = temp;
        }
    }

    return hit_anything;

}

bool ListOfHittables::is_hit(const Ray &ray, Interval t_range) const {
    return std::any_of(cbegin(entities), cend(entities), [&](const auto& entity) {
        return entity->is_hit(ray, {t_range.min(), t_range.max()});
    });
}
