#include "Viewport.h"

Viewport::Viewport(const ImageDimensions &dim, const Camera &cam) :
        m_height { 2 * calc_h(cam) * cam.focal_length() }
        , m_width {m_height * (static_cast<double>(dim.width) / gsl::narrow_cast<int>(dim.height))}
        , m_horizontal {cam.u() * m_width}
        , m_vertical {cam.v() * -m_height}
        , m_upper_left {
            cam.center()
            - (cam.focal_length() * cam.w())
            - (m_horizontal/2)
            - (m_vertical/2)
        }
        , m_horizontalPixelDelta {m_horizontal / gsl::narrow_cast<int>(dim.width)}
        , m_verticalPixelDelta {m_vertical / gsl::narrow_cast<int>(dim.height)}
        , m_pixel00 {m_upper_left + (0.5 * m_horizontalPixelDelta + m_verticalPixelDelta)}
{ }