//
// Created by avereniect on 12/22/21.
//

#ifndef AGS_CAMERA_HPP
#define AGS_CAMERA_HPP

#include "Common.hpp"

#include <cmath>

namespace ags::apt {

    struct Camera {
        mat4x4r transform{1.0f};

        vec3r foci{0.0f, 0.0f, 1.0f};
    };

}

#endif //AGS_CAMERA_HPP
