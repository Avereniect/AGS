//
// Created by avereniect on 5/19/22.
//

#ifndef AGS_APT_SHAPES_HPP
#define AGS_APT_SHAPES_HPP

#include "Common.hpp"

namespace ags::apt {

    struct Triangle {
        vec3r v0;
        vec3r v1;
        vec3r v2;
    };

    struct AABB {
        vec3r min;
        vec3r max;
    };

}

#endif //AGS_APT_SHAPES_HPP
