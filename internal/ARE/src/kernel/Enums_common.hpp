//
// Created by avereniect on 12/17/21.
//

#ifndef AGS_ARE_ENUMS_HPP
#define AGS_ARE_ENUMS_HPP

#include <ags/Types.hpp>
#include <ags/Logging.hpp>

#include <cstdint>

#include "ags/mesh/Attribute.hpp"

namespace ags::are {

    //=====================================================
    // Vertex Attribute Enums
    //=====================================================

    ///
    /// Enum used to represent how many components a vertex attribute has
    ///
    enum class Attribute_width : std::uint8_t {
        ZERO = 0,
        ONE = 1,
        TWO = 2,
        THREE = 3,
        FOUR = 4
    };

    ///
    /// Enum class representing
    ///
    enum class Attribute_type : std::uint8_t {
        NULL_ATTRIBUTE_TYPE,

        FLOAT32x1, FLOAT32x2, FLOAT32x3, FLOAT32x4,

        UINT32x1, UINT32x2, UINT32x3, UINT32x4,

        INT32x1, INT32x2, INT32x3, INT32x4,
    };

    Attribute_type to_attribute_type(Primitive p, are::Attribute_width w);

    Attribute_type to_attribute_type(Primitive p, mesh::Attribute_width w);

    std::size_t size_of_attribute_type(Attribute_type type);

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

        ARR_TEXTURE1D, ARR_TEXTURE2D,

        ARR_VEC1F, ARR_VEC2F, ARR_VEC3F, ARR_VEC4F,
        ARR_VEC1U, ARR_VEC2U, ARR_VEC3U, ARR_VEC4U,
        ARR_VEC1I, ARR_VEC2I, ARR_VEC3I, ARR_VEC4I,

        ARR_MAT2x2F, ARR_MAT2x3F, ARR_MAT2x4F,
        ARR_MAT3x2F, ARR_MAT3x3F, ARR_MAT3x4F,
        ARR_MAT4x2F, ARR_MAT4x3F, ARR_MAT4x4F
    };

    //=====================================================
    // Skybox enums
    //=====================================================

    enum class Cube_sides : std::uint8_t {
        NULL_CUBE_SIDE,
        TOP,
        BOTTOM,
        NORTH,
        EAST,
        SOUTH,
        WEST
    };

    //=====================================================
    // Texture enums
    //=====================================================

    ///
    ///
    ///
    enum class Channel_format : std::uint8_t {
        NULL_CHANNEL_FORMAT = 0, //No specified channel format

        ///
        /// One-component channels containing arbitrary data
        ///
        X = 1,

        ///
        /// Two-component channels containing arbitrary data
        ///
        XY = 2,

        ///
        /// Three-component channels containing arbitrary data
        ///
        XYZ = 3,

        ///
        /// Four-component channels containing arbitrary data
        ///
        XYZW = 4,


        ///
        /// Two-component channels containing sRGB encoded value channel and linear
        /// alpha component
        ///
        sV = 5,

        ///
        /// Two-component channels containing sRGB encoded value channel and linear
        /// alpha component
        ///
        sVA = 6,

        ///
        /// Three-component channels containing sRGB encoded RGB color
        ///
        sRGB = 7,

        ///
        /// Four-component channels containing sRGB encoded RGB color and a linear alpha component
        ///
        sRGBA = 8
    };

    enum class Texture_format : std::uint8_t {
        NULL_TEXTURE_FORMAT,
        X8U, XY8U, XYZ8U, XYZW8U,
        X16U, XY16U, XYZ16U, XYZW16U,
        X32U, XY32U, XYZ32U, XYZW32U,
        X16F, XY16F, XYZ16F, XYZW16F,
        X32F, XY32F, XYZ32F, XYZW32F
    };

    Texture_format to_texture_format(Channel_format c, Primitive t);

    Channel_format to_channel_format(Texture_format);

    Primitive to_primitive(Texture_format);

    //=====================================================
    // Framebuffer attachment enums
    //=====================================================

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

    ///
    /// \param f A combined depth-stencil buffer format enum
    /// \return True if the enum value has both a depth and stencil component.
    /// False otherwise
    bool is_combined_format(Depth_stencil_format f);





    ///
    /// Enum which is used to indicate how many samples should be used for
    /// multisampling while rendering
    ///
    enum class Sample_count : std::uint8_t {
        S1 = 1,
        S2 = 2,
        S4 = 4,
        S8 = 8,
        S16 = 16,
        S32 = 32
    };

    //=====================================================
    // Sampler enums
    //=====================================================

    ///
    ///
    ///
    enum class Texture_wrap : std::uint8_t {
        NULL_WRAP = 0,
        REPEAT = 1,
        MIRRORED_REPEAT = 2,
        CLAMP = 3
    };

    ///
    /// Enums used for representing texture filtering methods
    ///
    enum class Texture_filter : std::uint8_t {
        NULL_FILTER = 0,
        NEAREST = 1,
        LINEAR = 2
    };

    ///
    /// Enums used for representing mipmap filtering methods
    ///
    enum class Mipmap_filter : std::uint8_t {
        NULL_MIPMAP_FILTER = 0,
        NEAREST = 1,
        LINEAR = 2
    };

    //=====================================================
    // Queue enums
    //=====================================================

    ///
    /// Enum which is used to indicate whether a queue will be submitted
    /// multiple times
    ///
    enum class Queue_usage : std::uint8_t {
        NULL_QUEUE_USAGE,
        SINGLE,
        MULTIPLE
    };

}

#endif //AGS_ARE_ENUMS_HPP
