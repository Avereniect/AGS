#ifndef AGS_ARE_RENDER_SETTINGS_HPP
#define AGS_ARE_RENDER_SETTINGS_HPP

#include <cstdint>

#include <aul/Span.hpp>

#include "Common.hpp"
#include "Camera.hpp"

namespace ags::apt {

    //=====================================================
    // Render setting types
    //=====================================================

    ///
    ///
    ///
    enum class Pixel_filter {
        BOX,
        PYRAMID,
        CONE,
        HAN,
        LANCZOS
    };

    ///
    /// Enum used by APT to indicate which method is used to generate sample
    /// locations.
    ///
    enum class Sampling_pattern {
        ///
        /// Sampling locations are chosen at random
        ///
        WHITE_NOISE,

        ///
        /// Sampling locations are chosen using a stratified technique
        ///
        STRATIFIED_NOISE
    };

    enum class Shadow_ray_sampling {
        SAMPLE_ALL,
        SAMPLE_RANDOM,
        // MULTIPLE_IMPORTANCE_LIGHT_TREE
    };

    ///
    /// Struct containing the settings used for rendering by APT.
    ///
    struct Render_settings {
        std::uint32_t image_width = 800;
        std::uint32_t image_height = 600;

        Sampling_pattern sampling_pattern = Sampling_pattern::WHITE_NOISE;
        std::uint32_t samples_per_pixel = 32;

        std::uint32_t thread_count = 4;

        std::uint32_t recursion_depth_limit = 1;

        aul::Span<Camera> cameras;
    };

}

#endif //AGS_ARE_RENDER_SETTINGS_HPP
