#ifndef AGS_ARE_CAMERA_HPP
#define AGS_ARE_CAMERA_HPP

#include "Common.hpp"

#include <cmath>

namespace ags::apt {

    struct Camera {

        ///
        /// Camera origin
        ///
        vec3r location{0.0, 0.0, 0.0};

        ///
        /// Camera up vector
        ///
        uvec3r up{0.0, 0.0, 1.0};

        ///
        /// Camera forward vector. Should be orthogonal to up vector
        ///
        uvec3r forward{0.0, 0.0, -1.0};

        ///
        /// Width of camera sensor's larger dimension
        ///
        real sensor_size = 2.0;

        ///
        /// X, Y offset
        ///
        vec2r offset{0.0, 0.0};

        ///
        /// Camera focal length
        ///
        real focal_length = 1.0;

    };

}

#endif //AGS_ARE_CAMERA_HPP
