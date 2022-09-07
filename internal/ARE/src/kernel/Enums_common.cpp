//
// Created by avereniect on 3/26/22.
//
#include "Enums_common.hpp"

namespace ags::are {

    //=====================================================
    // Vertex Attribute Enums
    //=====================================================

    Attribute_type to_attribute_type(Primitive p, Attribute_width w) {
        switch (p) {
        case Primitive::FLOAT32: {
            Attribute_type table[] = {
                Attribute_type::NULL_ATTRIBUTE_TYPE,
                Attribute_type::FLOAT32x1,
                Attribute_type::FLOAT32x2,
                Attribute_type::FLOAT32x3,
                Attribute_type::FLOAT32x4
            };

            return table[int(w)];
        }
        case Primitive::UINT32: {
            Attribute_type table[] = {
                Attribute_type::NULL_ATTRIBUTE_TYPE,
                Attribute_type::UINT32x1,
                Attribute_type::UINT32x2,
                Attribute_type::UINT32x3,
                Attribute_type::UINT32x4
            };

            return table[int(w)];
        }
        case Primitive::INT32: {
            Attribute_type table[] = {
                Attribute_type::NULL_ATTRIBUTE_TYPE,
                Attribute_type::INT32x1,
                Attribute_type::INT32x2,
                Attribute_type::INT32x3,
                Attribute_type::INT32x4
            };

            return table[int(w)];
        }
        default:
            return Attribute_type::NULL_ATTRIBUTE_TYPE;
        }
    }

    Attribute_type to_attribute_type(Primitive p, mesh::Attribute_width w) {
        return to_attribute_type(
            p,
            are::Attribute_width(int(w))
        );
    }

    std::size_t size_of_attribute_type(Attribute_type type) {
        std::size_t x = size_of_primitive(attribute_primitive(type));
        std::size_t y = attribute_width(type);
        return x * y;
    }

    std::uint32_t attribute_width(Attribute_type type) {
        switch (type) {
        case Attribute_type::FLOAT32x1:
        case Attribute_type::UINT32x1:
        case Attribute_type::INT32x1:
            return 1;
        case Attribute_type::FLOAT32x2:
        case Attribute_type::UINT32x2:
        case Attribute_type::INT32x2:
            return 2;
        case Attribute_type::FLOAT32x3:
        case Attribute_type::UINT32x3:
        case Attribute_type::INT32x3:
            return 3;
        case Attribute_type::FLOAT32x4:
        case Attribute_type::UINT32x4:
        case Attribute_type::INT32x4:
            return 4;
        default:
            AGS_ERROR("Unrecognized vertex attribute type");
            return 0;
        }
    }

    Primitive attribute_primitive(Attribute_type type) {
        switch (type) {
        case Attribute_type::FLOAT32x1:
        case Attribute_type::FLOAT32x2:
        case Attribute_type::FLOAT32x3:
        case Attribute_type::FLOAT32x4:
            return Primitive::FLOAT32;

        case Attribute_type::UINT32x1:
        case Attribute_type::UINT32x2:
        case Attribute_type::UINT32x3:
        case Attribute_type::UINT32x4:
            return Primitive::UINT32;

        case Attribute_type::INT32x1:
        case Attribute_type::INT32x2:
        case Attribute_type::INT32x3:
        case Attribute_type::INT32x4:
            return Primitive::INT32;

        default:
            AGS_ERROR("Unrecognized vertex attribute type enum");
            return Primitive::NULL_PRIMITIVE;
        }
    }

    //=====================================================
    // Texture format enums
    //=====================================================

    Texture_format to_texture_format(Channel_format c, Primitive p) {
        auto i = static_cast<std::uint32_t>(c);

        switch (p) {
        case Primitive::UINT8: {
            static const Texture_format table[]{
                Texture_format::X8U,
                Texture_format::XY8U,
                Texture_format::XYZ8U,
                Texture_format::XYZW8U
            };
            return table[i];
        }
        case Primitive::UINT16: {
            static const Texture_format table[]{
                Texture_format::X16U,
                Texture_format::XY16U,
                Texture_format::XYZ16U,
                Texture_format::XYZW16U
            };
            return table[i];
        }
        case Primitive::UINT32: {
            static const Texture_format table[]{
                Texture_format::X32U,
                Texture_format::XY32U,
                Texture_format::XYZ32U,
                Texture_format::XYZW32U
            };
            return table[i];
        }
        case Primitive::FLOAT16: {
            static const Texture_format table[]{
                Texture_format::X16F,
                Texture_format::XY16F,
                Texture_format::XYZ16F,
                Texture_format::XYZW16F
            };
            return table[i];
        }
        case Primitive::FLOAT32: {
            static const Texture_format table[]{
                Texture_format::X32F,
                Texture_format::XY32F,
                Texture_format::XYZ32F,
                Texture_format::XYZW32F
            };
            return table[i];
        }
        default:
            return Texture_format::NULL_TEXTURE_FORMAT;
        }
    }

    Channel_format to_channel_format(Texture_format f) {
        switch (f) {
        case Texture_format::X8U:
        case Texture_format::X16U:
        case Texture_format::X32U:
        case Texture_format::X16F:
        case Texture_format::X32F:
            return Channel_format::X;
        case Texture_format::XY8U:
        case Texture_format::XY16U:
        case Texture_format::XY32U:
        case Texture_format::XY16F:
        case Texture_format::XY32F:
            return Channel_format::XY;
        case Texture_format::XYZ8U:
        case Texture_format::XYZ16U:
        case Texture_format::XYZ32U:
        case Texture_format::XYZ16F:
        case Texture_format::XYZ32F:
            return Channel_format::XYZ;
        case Texture_format::XYZW8U:
        case Texture_format::XYZW16U:
        case Texture_format::XYZW32U:
        case Texture_format::XYZW16F:
        case Texture_format::XYZW32F:
            return Channel_format::XYZW;
        default:
            AGS_ERROR("Unrecognized enum value");
            return Channel_format::NULL_CHANNEL_FORMAT;
        }
    }

    Primitive to_primitive(Texture_format f) {
        switch (f) {
        case Texture_format::X8U:
        case Texture_format::XY8U:
        case Texture_format::XYZ8U:
        case Texture_format::XYZW8U:
            return Primitive::UINT8;
        case Texture_format::X16U:
        case Texture_format::XY16U:
        case Texture_format::XYZ16U:
        case Texture_format::XYZW16U:
            return Primitive::UINT16;
        case Texture_format::X32U:
        case Texture_format::XY32U:
        case Texture_format::XYZ32U:
        case Texture_format::XYZW32U:
            return Primitive::UINT32;
        case Texture_format::X16F:
        case Texture_format::XY16F:
        case Texture_format::XYZ16F:
        case Texture_format::XYZW16F:
            return Primitive::FLOAT16;
        case Texture_format::X32F:
        case Texture_format::XY32F:
        case Texture_format::XYZ32F:
        case Texture_format::XYZW32F:
            return Primitive::FLOAT32;
        default:
            AGS_ERROR("Unrecognized enum value");
            return Primitive::NULL_PRIMITIVE;
        }
    }

    //=====================================================
    // Framebuffer attachment enums
    //=====================================================

    Depth_stencil_format to_depth_stencil_format(Depth_format d) {
        return Depth_stencil_format(std::uint8_t(d));
    }

    Depth_stencil_format to_depth_stencil_format(Stencil_format s) {
        return Depth_stencil_format(std::uint8_t(s));
    }

    Depth_stencil_format to_depth_stencil_format(Depth_format d, Stencil_format s) {
        return Depth_stencil_format{std::uint8_t(std::uint8_t(d) | std::uint8_t(s))};
    }

    Depth_format to_depth_format(Depth_stencil_format ds) {
        return Depth_format{std::uint8_t(std::uint8_t(ds) & 0x06)};
    }

    Stencil_format to_stencil_format(Depth_stencil_format ds) {
        std::uint32_t ret = static_cast<std::uint32_t>(ds) & 0x01;
        return static_cast<Stencil_format>(ret);
    }

    bool is_combined_format(Depth_stencil_format f) {
        return
            (f == Depth_stencil_format::INT24_STENCIL8) ||
            (f == Depth_stencil_format::FLOAT32_STENCIL8);
    }

}
