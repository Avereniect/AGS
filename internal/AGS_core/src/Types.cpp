//
// Created by avereniect on 11/29/21.
//

#include "ags/AGS_types.hpp"

namespace ags {

    std::size_t size_of_primitive(Primitive primitive) {
        switch (primitive) {
        case Primitive::NULL_PRIMITIVE: return 0;

        case Primitive::UINT8: return 1;
        case Primitive::UINT16: return 2;
        case Primitive::UINT32: return 4;
        case Primitive::UINT64: return 8;

        case Primitive::INT8: return 1;
        case Primitive::INT16: return 2;
        case Primitive::INT32: return 4;
        case Primitive::INT64: return 8;

        case Primitive::FLOAT16: return 2;
        case Primitive::FLOAT32: return 4;
        case Primitive::FLOAT64: return 8;
        default:
            return -1;
        }
    }

}