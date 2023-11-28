#pragma once

#include "Vec3.h"
#include "Camera.h"
#include "ImageDimensions.h"
#include "gsl/gsl"

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
    Viewport(const ImageDimensions& dim, const Camera& cam);

    // getters
    [[nodiscard]] double width() const { return m_width; }
    [[nodiscard]] const Point3 &upper_left() const { return m_upper_left; }
    [[nodiscard]] const Vec3 &horizontal() const { return m_horizontal; }
    [[nodiscard]] const Vec3 &vertical() const { return m_vertical; }
    [[nodiscard]] const PixelDelta &horizontal_pixel_delta() const { return m_horizontalPixelDelta; }
    [[nodiscard]] const PixelDelta &vertical_pixel_delta() const { return m_verticalPixelDelta; }
    [[nodiscard]] const Point3 &pixel00() const { return m_pixel00; }

};
