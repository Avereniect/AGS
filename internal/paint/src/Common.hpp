//
// Created by avereniect on 6/4/22.
//

#ifndef AGS_PAINT_COMMON_HPP
#define AGS_PAINT_COMMON_HPP

#include <ags/image/Pixel_buffer.hpp>
#include <ags/image/Canvas.hpp>

#include <avml/AVML.hpp>

#include <climits>

namespace ags::paint {

    //=====================================================
    // Assertions
    //=====================================================

    static_assert(CHAR_BIT == 8);
    static_assert(sizeof(float) == 4);

    //=====================================================
    // Primitive types
    //=====================================================

    using real = float;

    using uint8  = std::uint8_t;
    using uint16 = std::uint16_t;
    using uint32 = std::uint32_t;
    using uint64 = std::uint64_t;

    using int8  = std::int8_t;
    using int16 = std::int16_t;
    using int32 = std::int32_t;
    using int64 = std::int64_t;

    //=====================================================
    // Linear Algebra Types
    //=====================================================

    using vec2r = avml::vec2f;
    using vec3r = avml::vec3f;
    using vec4r = avml::vec4f;

    using mat2x2r = avml::mat2x2f;
    using mat3x3r = avml::mat3x3f;
    using mat4x4r = avml::mat4x4f;

    //=====================================================
    // Pixel_buffer_types
    //=====================================================

    using Pixel_buffer_X_8u = image::Pixel_buffer<std::uint8_t, 1>;
    using Pixel_buffer_XY_8u = image::Pixel_buffer<std::uint8_t, 2>;
    using Pixel_buffer_XYZ_8u = image::Pixel_buffer<std::uint8_t, 3>;
    using Pixel_buffer_XYZW_8u = image::Pixel_buffer<std::uint8_t, 4>;

    //=====================================================
    // Canvas types
    //=====================================================

    using Canvas_X_8u = image::Canvas<std::uint8_t, 1>;
    using Canvas_XY_8u = image::Canvas<std::uint8_t, 2>;
    using Canvas_XYZ_8u = image::Canvas<std::uint8_t, 3>;
    using Canvas_XYZW_8u = image::Canvas<std::uint8_t, 4>;

    using Canvas_X_16u = image::Canvas<uint16_t, 1>;
    using Canvas_XY_16u = image::Canvas<uint16_t, 2>;
    using Canvas_XYZ_16u = image::Canvas<uint16_t, 3>;
    using Canvas_XYZW_16u = image::Canvas<uint16_t, 4>;

    using Canvas_X_32f = image::Canvas<float, 1>;
    using Canvas_XY_32f = image::Canvas<float, 2>;
    using Canvas_XYZ_32f = image::Canvas<float, 3>;
    using Canvas_XYZW_32f = image::Canvas<float, 4>;

    //=====================================================
    // Channel format
    //=====================================================

    using ags::image::Channel_format;

}

#endif //AGS_PAINT_COMMON_HPP
