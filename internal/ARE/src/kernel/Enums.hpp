//
// Created by avereniect on 12/17/21.
//

#ifndef AGS_ARE_ENUMS_HPP
#define AGS_ARE_ENUMS_HPP

#include <cstdint>

namespace ags::are {

    enum class Attribute_type : std::uint8_t {
        NULL_ATTRIBUTE_TYPE,

        FLOAT16, FLOAT32, FLOAT64,

        INT8, UINT8,
        INT16, UINT16,
        INT32, UINT32
    };

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
