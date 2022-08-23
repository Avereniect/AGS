//
// Created by avereniect on 3/26/22.
//
#include "Enums.hpp"

namespace ags::are {

    //=====================================================
    // Vertex Attribute Enums
    //=====================================================

    std::uint32_t attribute_width(Attribute_type type) {
        switch (type) {
        case Attribute_type::FLOAT16x1:
        case Attribute_type::FLOAT32x1:
        case Attribute_type::FLOAT64x1:
        case Attribute_type::UINT8x1:
        case Attribute_type::UINT16x1:
        case Attribute_type::UINT32x1:
        case Attribute_type::INT8x1:
        case Attribute_type::INT16x1:
        case Attribute_type::INT32x1:
            return 1;
        case Attribute_type::FLOAT16x2:
        case Attribute_type::FLOAT32x2:
        case Attribute_type::FLOAT64x2:
        case Attribute_type::UINT8x2:
        case Attribute_type::UINT16x2:
        case Attribute_type::UINT32x2:
        case Attribute_type::INT8x2:
        case Attribute_type::INT16x2:
        case Attribute_type::INT32x2:
            return 2;
        case Attribute_type::FLOAT16x3:
        case Attribute_type::FLOAT32x3:
        case Attribute_type::FLOAT64x3:
        case Attribute_type::UINT8x3:
        case Attribute_type::UINT16x3:
        case Attribute_type::UINT32x3:
        case Attribute_type::INT8x3:
        case Attribute_type::INT16x3:
        case Attribute_type::INT32x3:
            return 3;
        case Attribute_type::FLOAT16x4:
        case Attribute_type::FLOAT32x4:
        case Attribute_type::FLOAT64x4:
        case Attribute_type::UINT8x4:
        case Attribute_type::UINT16x4:
        case Attribute_type::UINT32x4:
        case Attribute_type::INT8x4:
        case Attribute_type::INT16x4:
        case Attribute_type::INT32x4:
            return 4;
        default:
            AGS_ERROR("Unrecognized vertex attribute type enum at " AGS_CODE_LOCATION);
            return 0;
        }
    }

    Primitive attribute_primitive(Attribute_type type) {
        switch (type) {
        case Attribute_type::FLOAT16x1:
        case Attribute_type::FLOAT16x2:
        case Attribute_type::FLOAT16x3:
        case Attribute_type::FLOAT16x4:
            return Primitive::FLOAT16;

        case Attribute_type::FLOAT32x1:
        case Attribute_type::FLOAT32x2:
        case Attribute_type::FLOAT32x3:
        case Attribute_type::FLOAT32x4:
            return Primitive::FLOAT32;

        case Attribute_type::FLOAT64x1:
        case Attribute_type::FLOAT64x2:
        case Attribute_type::FLOAT64x3:
        case Attribute_type::FLOAT64x4:
            return Primitive::FLOAT64;

        case Attribute_type::UINT8x1:
        case Attribute_type::UINT8x2:
        case Attribute_type::UINT8x3:
        case Attribute_type::UINT8x4:
            return Primitive::UINT8;

        case Attribute_type::UINT16x1:
        case Attribute_type::UINT16x2:
        case Attribute_type::UINT16x3:
        case Attribute_type::UINT16x4:
            return Primitive::UINT16;

        case Attribute_type::UINT32x1:
        case Attribute_type::UINT32x2:
        case Attribute_type::UINT32x3:
        case Attribute_type::UINT32x4:
            return Primitive::UINT32;

        case Attribute_type::INT8x1:
        case Attribute_type::INT8x2:
        case Attribute_type::INT8x3:
        case Attribute_type::INT8x4:
            return Primitive::INT8;

        case Attribute_type::INT16x1:
        case Attribute_type::INT16x2:
        case Attribute_type::INT16x3:
        case Attribute_type::INT16x4:
            return Primitive::INT16;

        case Attribute_type::INT32x1:
        case Attribute_type::INT32x2:
        case Attribute_type::INT32x3:
        case Attribute_type::INT32x4:
            return Primitive::INT32;

        default:
            AGS_ERROR("Unrecognized vertex attribute type enum at " AGS_CODE_LOCATION);
            return Primitive::NULL_PRIMITIVE;
        }
    }

    //=====================================================
    // Shader Uniform Enums
    //=====================================================

    Depth_stencil_format to_depth_stencil_format(Depth_format d) {
        return Depth_stencil_format{d};
    }

    Depth_stencil_format to_depth_stencil_format(Stencil_format s) {
        return Depth_stencil_format{s};
    }

    Depth_stencil_format to_depth_stencil_format(Depth_format d, Stencil_format s) {
        return Depth_stencil_format{std::uint8_t(std::uint8_t(d) | std::uint8_t(s))};
    }

    Depth_format to_depth_format(Depth_stencil_format ds) {
        return Depth_format{std::uint8_t(std::uint8_t(ds) & 0x06)};
    }

    Stencil_format to_stencil_format(Depth_stencil_format ds) {
        return Stencil_format{std::uint8_t(std::uint8_t(ds) & 0x01)};
    }

    bool is_combined_format(Depth_stencil_format f) {
        return
            (f == Depth_stencil_format::INT24_STENCIL8) ||
            (f == Depth_stencil_format::FLOAT32_STENCIL8);
    }

}
