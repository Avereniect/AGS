//
// Created by avereniect on 3/10/22.
//

#ifndef AGS_STROKE_2D_SETTINGS_HPP
#define AGS_STROKE_2D_SETTINGS_HPP

#include "../Types.hpp"

namespace ags::paint {

    struct Stroke_settings {
        vec2r start{};
        vec2r end{};

        vec4r color{};
        real strength = 1.0;
    };

}

#endif //AGS_STROKE_2D_SETTINGS_HPP
