//
// Created by avereniect on 12/22/21.
//

#ifndef AGS_ARE_RENDER_SETTINGS_HPP
#define AGS_ARE_RENDER_SETTINGS_HPP

#include <cstdint>

#include "Common.hpp"

namespace ags::apt {

    //=====================================================
    // Render setting types
    //=====================================================

    enum class Pixel_filter {
        BOX,
        GAUSSIAN
    };

    struct Render_settings {
        std::uint32_t image_width = 800;
        std::uint32_t image_height = 600;

        std::uint32_t samples_per_pixel = 4;
        Pixel_filter pixel_filter = Pixel_filter::BOX;
        real pixel_filter_width = 1.0;

        std::uint32_t thread_count = 4;

        std::uint32_t recursion_depth_limit = 1;
    };

}

#endif //AGS_ARE_RENDER_SETTINGS_HPP
