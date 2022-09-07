//
// Created by avereniect on 5/3/22.
//
#include "Enums.hpp"

#include <ags/Logging.hpp>

namespace ags::are::gl_kernel {

    GLenum to_native_enum(Channel_format format) {
        switch (format) {
        case Channel_format::NULL_CHANNEL_FORMAT:
            return 0;
        case Channel_format::X:
            return GL_RED;
        case Channel_format::XY:
            return GL_RG;
        case Channel_format::XYZ:
            return GL_RGB;
        case Channel_format::XYZW:
            return GL_RGBA;
        default:
            AGS_ERROR("Unrecognized enum value encountered at " AGS_CODE_LOCATION);
            return 0;
        }
    }

    GLenum to_native_enum(Primitive primitive) {
        switch (primitive) {
        case Primitive::NULL_PRIMITIVE:
            return 0;
        case Primitive::UINT8:
            return GL_UNSIGNED_BYTE;
        case Primitive::UINT16:
            return GL_UNSIGNED_SHORT;
        case Primitive::UINT32:
            return GL_UNSIGNED_INT;
        case Primitive::UINT64:
            AGS_ERROR("Error in " AGS_CODE_LOCATION "\nOpenGL does not have an enum corresponding to uint64_t.");
            return 0;
        case Primitive::INT8:
            return GL_BYTE;
        case Primitive::INT16:
            return GL_SHORT;
        case Primitive::INT32:
            return GL_INT;
        case Primitive::INT64:
            AGS_ERROR("Error in " AGS_CODE_LOCATION "\nOpenGL does not have an enum corresponding to uint64_t.");
            return 0;
        case Primitive::FLOAT16:
            return GL_HALF_FLOAT;
        case Primitive::FLOAT32:
            return GL_FLOAT;
        case Primitive::FLOAT64:
            return GL_DOUBLE;
        default:
            AGS_ERROR("Unrecognized enum value");
            return 0;
        }
    }

    GLint to_native_enum(Channel_format format, Primitive primitive) {
        switch (primitive) {
        case Primitive::UINT8: {
            constexpr GLenum table[]{GL_R8, GL_RG8, GL_RGB8, GL_RGBA8};
            return table[static_cast<std::uint8_t>(format) - 1];
        }
        case Primitive::UINT16: {
            constexpr GLenum table[]{GL_R16, GL_RG16, GL_RGB16, GL_RGBA16};
            return table[static_cast<std::uint8_t>(format) - 1];
        }
        case Primitive::FLOAT32: {
            constexpr GLenum table[]{GL_R32F, GL_RG32F, GL_RGB32F, GL_RGBA32F};
            return table[static_cast<std::uint8_t>(format) - 1];
        }
        default:
            AGS_ERROR("Unrecognized enum value");
            return 0;
        }
    }

    GLenum to_native_enum(Depth_format format) {
        switch (format) {
        case Depth_format::NULL_DEPTH_FORMAT:
            return 0;
        case Depth_format::INT24:
            return GL_DEPTH_COMPONENT24;
        case Depth_format::FLOAT32:
            return GL_DEPTH_COMPONENT32F;
        default:
            AGS_ERROR("Unrecognized enum value");
            return 0;
        }
    }

    GLenum to_native_enum(Stencil_format format) {
        switch (format) {
        case Stencil_format::NULL_STENCIL_FORMAT:
            return 0;
        case Stencil_format::STENCIL8:
            return GL_STENCIL_INDEX8;
        default:
            AGS_ERROR("Unrecognized enum value");
            return 0;
        }
    }

    GLenum to_native_enum(Depth_stencil_format format) {
        switch (format) {
        case Depth_stencil_format::NULL_DEPTH_STENCIL_FORMAT:
            return 0;
        case Depth_stencil_format::INT24:
            return GL_DEPTH_COMPONENT24;
        case Depth_stencil_format::FLOAT32:
            return GL_DEPTH_COMPONENT32F;
        case Depth_stencil_format::STENCIL8:
            return GL_STENCIL_INDEX8;
        case Depth_stencil_format::INT24_STENCIL8:
            return GL_DEPTH24_STENCIL8;
        case Depth_stencil_format::FLOAT32_STENCIL8:
            return GL_DEPTH32F_STENCIL8;
        default:
            AGS_ERROR("Unrecognized enum value");
            return 0;
        }
    }

    GLint to_native_enum(Texture_wrap wrap) {
        GLint table[3] {GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE};

        return table[std::uint8_t(wrap) - 1];
    }

    GLint to_native_enum(Texture_filter tex_filter) {
        GLint table[2] {GL_NEAREST, GL_LINEAR};

        return table[std::uint8_t(tex_filter) - 1];
    }

    GLint to_native_enum(Texture_filter tex_filter, Mipmap_filter mip_filter) {
        GLint table[3][2] {
            {GL_NEAREST, GL_LINEAR},
            {GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST},
            {GL_NEAREST_MIPMAP_LINEAR,  GL_LINEAR_MIPMAP_LINEAR}
        };

        return table[std::uint8_t(mip_filter)][std::uint8_t(tex_filter) - 1];
    }

    Primitive to_primitive(GLenum type) {
        switch (type) {
        case GL_UNSIGNED_BYTE: return Primitive::UINT8;
        case GL_UNSIGNED_SHORT: return Primitive::UINT16;
        case GL_UNSIGNED_INT: return Primitive::UINT32;
        case GL_BYTE: return Primitive::INT8;
        case GL_SHORT: return Primitive::INT16;
        case GL_INT: return Primitive::INT32;
        case GL_HALF_FLOAT: return Primitive::FLOAT16;
        case GL_FLOAT: return Primitive::FLOAT32;
        case GL_DOUBLE: return Primitive::FLOAT64;
        default:
            AGS_ERROR("Unrecognized OpenGL type enum");
            return Primitive::NULL_PRIMITIVE;
        }
    }

    Attribute_type to_attribute_type(GLenum attribute_type) {
        switch (attribute_type) {
        case GL_FLOAT:      return Attribute_type::FLOAT32x1;
        case GL_FLOAT_VEC2: return Attribute_type::FLOAT32x2;
        case GL_FLOAT_VEC3: return Attribute_type::FLOAT32x3;
        case GL_FLOAT_VEC4: return Attribute_type::FLOAT32x4;

        case GL_INT:      return Attribute_type::INT32x1;
        case GL_INT_VEC2: return Attribute_type::INT32x2;
        case GL_INT_VEC3: return Attribute_type::INT32x3;
        case GL_INT_VEC4: return Attribute_type::INT32x4;

        case GL_UNSIGNED_INT:      return Attribute_type::UINT32x1;
        case GL_UNSIGNED_INT_VEC2: return Attribute_type::UINT32x2;
        case GL_UNSIGNED_INT_VEC3: return Attribute_type::UINT32x3;
        case GL_UNSIGNED_INT_VEC4: return Attribute_type::UINT32x4;

        default:
            AGS_ERROR("Unrecognized attribute type enum");
            return Attribute_type::NULL_ATTRIBUTE_TYPE;
        }
    }

    Uniform_type to_uniform_type(GLenum uniform_type) {
        switch (uniform_type) {
        case GL_SAMPLER_1D: return Uniform_type::TEXTURE1D;
        case GL_SAMPLER_2D: return Uniform_type::TEXTURE2D;
        case GL_SAMPLER_3D: return Uniform_type::TEXTURE3D;

        case GL_FLOAT:      return Uniform_type::VEC1F;
        case GL_FLOAT_VEC2: return Uniform_type::VEC2F;
        case GL_FLOAT_VEC3: return Uniform_type::VEC3F;
        case GL_FLOAT_VEC4: return Uniform_type::VEC4F;

        case GL_UNSIGNED_INT:      return Uniform_type::VEC1U;
        case GL_UNSIGNED_INT_VEC2: return Uniform_type::VEC2U;
        case GL_UNSIGNED_INT_VEC3: return Uniform_type::VEC3U;
        case GL_UNSIGNED_INT_VEC4: return Uniform_type::VEC4U;

        case GL_INT:      return Uniform_type::VEC1I;
        case GL_INT_VEC2: return Uniform_type::VEC2I;
        case GL_INT_VEC3: return Uniform_type::VEC3I;
        case GL_INT_VEC4: return Uniform_type::VEC4I;

        case GL_FLOAT_MAT2:   return Uniform_type::MAT2x2F;
        case GL_FLOAT_MAT2x3: return Uniform_type::MAT2x3F;
        case GL_FLOAT_MAT2x4: return Uniform_type::MAT2x4F;

        case GL_FLOAT_MAT3x2: return Uniform_type::MAT3x2F;
        case GL_FLOAT_MAT3:   return Uniform_type::MAT3x3F;
        case GL_FLOAT_MAT3x4: return Uniform_type::MAT3x4F;

        case GL_FLOAT_MAT4x2: return Uniform_type::MAT4x2F;
        case GL_FLOAT_MAT4x3: return Uniform_type::MAT4x3F;
        case GL_FLOAT_MAT4:   return Uniform_type::MAT4x4F;

        case GL_SAMPLER_1D_ARRAY: return Uniform_type::ARR_TEXTURE1D;
        case GL_SAMPLER_2D_ARRAY: return Uniform_type::ARR_TEXTURE2D;

        default: return Uniform_type::NULL_UNIFORM_TYPE;
        }
    }

}
