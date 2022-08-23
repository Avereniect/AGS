//
// Created by avereniect on 12/17/21.
//

#ifndef AGS_ARE_ENUMS_HPP
#define AGS_ARE_ENUMS_HPP

#include <ags/Types.hpp>
#include <ags/Logging.hpp>

#include <cstdint>

namespace ags::are {

    //=====================================================
    // Vertex Attribute Enums
    //=====================================================

    enum class Attribute_width : std::uint8_t {
        ZERO = 0,
        ONE = 1,
        TWO = 2,
        THREE = 3,
        FOUR = 4
    };

    enum class Attribute_type : std::uint8_t {
        NULL_ATTRIBUTE_TYPE,

        FLOAT16x1, FLOAT16x2, FLOAT16x3, FLOAT16x4,
        FLOAT32x1, FLOAT32x2, FLOAT32x3, FLOAT32x4,
        FLOAT64x1, FLOAT64x2, FLOAT64x3, FLOAT64x4,

        UINT8x1,  UINT8x2,  UINT8x3,  UINT8x4,
        UINT16x1, UINT16x2, UINT16x3, UINT16x4,
        UINT32x1, UINT32x2, UINT32x3, UINT32x4,

        INT8x1,  INT8x2,  INT8x3,  INT8x4,
        INT16x1, INT16x2, INT16x3, INT16x4,
        INT32x1, INT32x2, INT32x3, INT32x4,
    };

    std::uint32_t attribute_width(Attribute_type type);

    Primitive attribute_primitive(Attribute_type type);

    //=====================================================
    // Shader Uniform Enums
    //=====================================================

    enum class Uniform_type : std::uint8_t {
        NULL_UNIFORM_TYPE,

        TEXTURE1D, TEXTURE2D, TEXTURE3D,

        VEC1F, VEC2F, VEC3F, VEC4F,
        VEC1U, VEC2U, VEC3U, VEC4U,
        VEC1I, VEC2I, VEC3I, VEC4I,

        MAT2x2F, MAT2x3F, MAT2x4F,
        MAT3x2F, MAT3x3F, MAT3x4F,
        MAT4x2F, MAT4x3F, MAT4x4F,

        ARR_TEXTURE1D, ARR_TEXTURE2D, ARR_TEXTURE3D,

        ARR_VEC1F, ARR_VEC2F, ARR_VEC3F, ARR_VEC4F,
        ARR_VEC1U, ARR_VEC2U, ARR_VEC3U, ARR_VEC4U,
        ARR_VEC1I, ARR_VEC2I, ARR_VEC3I, ARR_VEC4I,

        ARR_MAT2x2F, ARR_MAT2x3F, ARR_MAT2x4F,
        ARR_MAT3x2F, ARR_MAT3x3F, ARR_MAT3x4F,
        ARR_MAT4x2F, ARR_MAT4x3F, ARR_MAT4x4F
    };

    enum class Cube_sides : std::uint8_t {
        NULL_CUBE_SIDE,
        TOP,
        BOTTOM,
        NORTH,
        EAST,
        SOUTH,
        WEST
    };

    enum class Channel_format : std::uint8_t {
        NULL_CHANNEL_FORMAT,
        X,
        XY,
        XYZ,
        XYZW
    };

    enum class Depth_format : std::uint8_t {
        NULL_DEPTH_FORMAT = 0x00,
        INT24 = 0x02,
        FLOAT32 = 0x04
    };

    enum class Stencil_format : std::uint8_t {
        NULL_STENCIL_FORMAT = 0x00,
        STENCIL8 = 0x01
    };

    enum class Depth_stencil_format : std::uint8_t {
        NULL_DEPTH_STENCIL_FORMAT = 0x00,
        INT24 = 0x02,
        FLOAT32 = 0x04,

        STENCIL8 = 0x01,

        INT24_STENCIL8 = 0x03,
        FLOAT32_STENCIL8 = 0x05
    };

    enum class Queue_usage : std::uint8_t {
        NULL_QUEUE_USAGE,
        SINGLE,
        MULTIPLE
    };

    Depth_stencil_format to_depth_stencil_format(Depth_format);
    Depth_stencil_format to_depth_stencil_format(Stencil_format);
    Depth_stencil_format to_depth_stencil_format(Depth_format, Stencil_format);

    Depth_format to_depth_format(Depth_stencil_format);
    Stencil_format to_stencil_format(Depth_stencil_format);

    bool is_combined_format(Depth_stencil_format);

    enum class Sample_count : std::uint8_t {
        S1,
        S2,
        S4,
        S8,
        S16,
        S32
    };

}

#endif //AGS_ARE_ENUMS_HPP
