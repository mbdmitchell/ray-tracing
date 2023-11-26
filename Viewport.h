#pragma once

#include "Vec3.h"
#include "Render.h"
#include "Camera.h"
#include "ImageDimensions.h"

class Viewport {
public:
    using PixelDelta = Vec3;
private:
    double m_height;
    double m_width;
    Point3 m_upper_left;
    Vec3 m_horizontal;
    Vec3 m_vertical;
    PixelDelta m_horizontalPixelDelta;
    PixelDelta m_verticalPixelDelta;
    Point3 m_pixel00;
public:
    Viewport(const ImageDimensions& dim, const Camera& cam) :
        m_height {2.0}  // Hard-coded for now
        , m_width {m_height * (static_cast<double>(dim.width) / gsl::narrow_cast<int>(dim.height))}
        , m_upper_left {cam.center - Vec3{0, 0, cam.focal_length}
                                 - Vec3{m_width, 0, 0} / 2
                                 - Vec3{0, -m_height, 0} / 2}
        , m_horizontal {m_width,0,0}
        , m_vertical {0,-m_height,0}
        , m_horizontalPixelDelta {m_horizontal / gsl::narrow_cast<int>(dim.width)}
        , m_verticalPixelDelta {m_vertical / gsl::narrow_cast<int>(dim.height)}
        , m_pixel00 {m_upper_left + (0.5 * m_horizontalPixelDelta + m_verticalPixelDelta)}
    { }

    // getters
    [[nodiscard]] double width() const { return m_width; }
    [[nodiscard]] const Point3 &upper_left() const { return m_upper_left; }
    [[nodiscard]] const Vec3 &horizontal() const { return m_horizontal; }
    [[nodiscard]] const Vec3 &vertical() const { return m_vertical; }
    [[nodiscard]] const PixelDelta &horizontal_pixel_delta() const { return m_horizontalPixelDelta; }
    [[nodiscard]] const PixelDelta &vertical_pixel_delta() const { return m_verticalPixelDelta; }
    [[nodiscard]] const Point3 &pixel00() const { return m_pixel00; }

};
