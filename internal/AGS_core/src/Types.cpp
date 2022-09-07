//
// Created by avereniect on 11/29/21.
//

#include "ags/Types.hpp"

namespace ags {

    std::size_t size_of_primitive(Primitive primitive) {
        switch (primitive) {
        case Primitive::NULL_PRIMITIVE: return -1;

        case Primitive::UINT8: return sizeof(std::uint8_t);
        case Primitive::UINT16: return sizeof(std::uint16_t);
        case Primitive::UINT32: return sizeof(std::uint32_t);
        case Primitive::UINT64: return sizeof(std::uint64_t);

        case Primitive::INT8: return sizeof(std::int8_t);
        case Primitive::INT16: return sizeof(std::int16_t);
        case Primitive::INT32: return sizeof(std::int32_t);
        case Primitive::INT64: return sizeof(std::int64_t);

        case Primitive::FLOAT16: return sizeof(half);
        case Primitive::FLOAT32: return sizeof(float);
        case Primitive::FLOAT64: return sizeof(double);
        default:
            return -1;
        }
    }

    bool is_unsigned(Primitive primitive) {
        return
            (primitive == Primitive::UINT8)  ||
            (primitive == Primitive::UINT16) ||
            (primitive == Primitive::UINT32) ||
            (primitive == Primitive::UINT64);
    }

    bool is_integer(Primitive primitive) {
        return
            (primitive != Primitive::NULL_PRIMITIVE)  &&
            (primitive != Primitive::FLOAT16) &&
            (primitive != Primitive::FLOAT32) &&
            (primitive != Primitive::FLOAT64);
    }

    bool is_floating_point(Primitive primitive) {
        return
            (primitive == Primitive::FLOAT16) ||
            (primitive == Primitive::FLOAT32) ||
            (primitive == Primitive::FLOAT64);
    }

}