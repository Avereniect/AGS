//
// Created by avereniect on 11/27/21.
//

#ifndef AGS_AGS_TYPES_HPP
#define AGS_AGS_TYPES_HPP

#include <cstdint>

#include <half.hpp>

namespace ags {

    using half = half_float::half;

    enum class Primitive : std::uint8_t {
        NULL_PRIMITIVE,
        UINT8,
        UINT16,
        UINT32,
        UINT64,

        INT8,
        INT16,
        INT32,
        INT64,

        FLOAT16,
        FLOAT32,
        FLOAT64
    };

    std::size_t size_of_primitive(Primitive primitive);

    template<class T>
    struct as_primitive {
        static constexpr Primitive value = Primitive::NULL_PRIMITIVE;
    };

    template<class T>
    static constexpr Primitive as_primitive_v = as_primitive<T>::value;

    template<>
    struct as_primitive<std::uint8_t> {
        static constexpr Primitive value = Primitive::UINT8;
    };

    template<>
    struct as_primitive<std::uint16_t> {
        static constexpr Primitive value = Primitive::UINT16;
    };

    template<>
    struct as_primitive<std::uint32_t> {
        static constexpr Primitive value = Primitive::UINT32;
    };

    template<>
    struct as_primitive<std::uint64_t> {
        static constexpr Primitive value = Primitive::UINT64;
    };



    template<>
    struct as_primitive<std::int8_t> {
        static constexpr Primitive value = Primitive::INT8;
    };

    template<>
    struct as_primitive<std::int16_t> {
        static constexpr Primitive value = Primitive::INT16;
    };

    template<>
    struct as_primitive<std::int32_t> {
        static constexpr Primitive value = Primitive::INT32;
    };

    template<>
    struct as_primitive<std::int64_t> {
        static constexpr Primitive value = Primitive::INT64;
    };

    

    template<>
    struct as_primitive<half> {
        static constexpr Primitive value = Primitive::FLOAT16;
    };

    template<>
    struct as_primitive<float> {
        static constexpr Primitive value = Primitive::FLOAT32;
    };

    template<>
    struct as_primitive<double> {
        static constexpr Primitive value = Primitive::FLOAT64;
    };

}

#endif //AGS_AGS_TYPES_HPP
