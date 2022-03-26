//
// Created by avereniect on 12/22/21.
//

#ifndef AGS_RENDER_SETTINGS_HPP
#define AGS_RENDER_SETTINGS_HPP

#include <cstdint>

#include "Common.hpp"

namespace ags::apt {

    struct Render_settings {
        std::uint32_t image_width = 800;
        std::uint32_t image_height = 600;


        std::uint32_t samples_per_pixel = 4;


        std::uint32_t recursion_depth = 1;
    };

}

#endif //AGS_RENDER_SETTINGS_HPP
