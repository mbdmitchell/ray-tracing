#pragma once

#include "Vec3.h"
#include "Ray.h"
#include "Viewport.h"

class Camera {
    using Degrees = double;
    Point3 m_center;
    Degrees m_field_of_view = 20;   // Vertical view angle
    Point3 m_looking_from;          // Point camera is looking from
    Point3 m_looking_at;            // Point camera is looking at
    double m_focal_length;
    Vec3 m_rel_up;                  // Camera-relative "up" direction
    Vec3 m_w, m_u, m_v;             // Camera frame basis vectors

public:

    explicit Camera(Point3 looking_from = Point3{0,0,-1}
           , Point3 looking_at = Point3{0,0,0}
           , Vec3 rel_up = Vec3{0,1,0}
           )
        : m_center{looking_from}
        , m_looking_from{looking_from}
        , m_looking_at{looking_at}
        , m_focal_length{(m_looking_from - m_looking_at).length()}
        , m_rel_up{rel_up}
        , m_w{unit_vector(m_looking_from - m_looking_at)}
        , m_u{unit_vector(cross(m_rel_up, m_w))}
        , m_v{cross(m_w, m_u)} { }


    // getters
    [[nodiscard]] auto center() const {return m_center; }
    [[nodiscard]] auto focal_length() const {return m_focal_length; }
    [[nodiscard]] auto field_of_view() const {return m_field_of_view; }
    [[nodiscard]] auto w() const {return m_w;}
    [[nodiscard]] auto u() const {return m_u;}
    [[nodiscard]] auto v() const {return m_v;}
};