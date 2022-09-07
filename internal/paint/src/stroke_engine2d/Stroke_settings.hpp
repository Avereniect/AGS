//
// Created by avereniect on 3/10/22.
//

#ifndef AGS_STROKE_2D_SETTINGS_HPP
#define AGS_STROKE_2D_SETTINGS_HPP

#include "../Common.hpp"

namespace ags::paint {

    struct Dot_settings {
        vec2r location{};

        //channel_format_vector_t<f> color{};

        real strength = 1.0;
        real width = 1.0;
    };

    struct Stroke_settings {
        vec2r start{};
        vec2r end{};

        //channel_format_vector_t<f> color{};

        real strength = 1.0;
        real width = 1.0;
    };

}

#endif //AGS_STROKE_2D_SETTINGS_HPP
