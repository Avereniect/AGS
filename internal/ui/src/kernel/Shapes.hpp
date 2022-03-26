//
// Created by avereniect on 3/23/22.
//

#ifndef AGS_UI_SHAPES_HPP
#define AGS_UI_SHAPES_HPP

#include "Types.hpp"

namespace ags::ui::kernel {

    struct Stroke {
        vec3 color;
        float width;
    };

    struct Fill {

    };

    struct Circle {
        vec3 location{};
        float radius = 1.0f;
        std::uint32_t segments = 8;
    };

    struct Rect {
        vec3 location{};
        vec2 dimensions{1.0f, 1.0f};
    };

    struct Arc {
        float angle_begin = 0.0f;
        float angle_end = 6.28318530717958647692;

        vec3 location{};
        float radius = 1.0f;
        std::uint32_t segments = 8;
    };

    struct Round_rect {
        float bevel_radius = 1.0f;
        vec3 location{};
        vec2 dimensions{1.0f, 1.0f};
        std::uint32_t segments = 2;
    };

}

#endif //AGS_UI_SHAPES_HPP
