#include "Viewport.h"

Viewport::Viewport(const ImageDimensions &dim, const Camera &cam) :
        m_height {2.0}  // Hard-coded for now
        , m_width {m_height * (static_cast<double>(dim.width) / gsl::narrow_cast<int>(dim.height))}
        , m_upper_left {cam.center - Vec3{0, 0, cam.focal_length} - Vec3{m_width, 0, 0} / 2 - Vec3{0, -m_height, 0} / 2}
        , m_horizontal {m_width,0,0}
        , m_vertical {0,-m_height,0}
        , m_horizontalPixelDelta {m_horizontal / gsl::narrow_cast<int>(dim.width)}
        , m_verticalPixelDelta {m_vertical / gsl::narrow_cast<int>(dim.height)}
        , m_pixel00 {m_upper_left + (0.5 * m_horizontalPixelDelta + m_verticalPixelDelta)}
{ }