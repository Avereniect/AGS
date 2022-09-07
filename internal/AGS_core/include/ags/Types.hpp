//
// Created by avereniect on 11/27/21.
//

#ifndef AGS_CORE_TYPES_HPP
#define AGS_CORE_TYPES_HPP

#include <cstdint>

#include <half.hpp>

namespace ags {

    using half = half_float::half;

    ///
    /// Enum class used to represent fundamental integral and floating-point
    /// types. Although half floats are not fundamental types according to the
    /// C++ standard, their use is common in certain contexts relevant to the
    /// AGS project.
    ///
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

    ///
    /// \param primitive Arbitrary primitive size
    /// \return Size of an object of primitive type in bytes. Returns negative
    ///     one primitive is NULL_PRIMITIVE.
    std::size_t size_of_primitive(Primitive primitive);

    ///
    /// \param primitive Arbitrary primitive size
    /// \return Return true if primitive represents an unsigned integral type
    bool is_unsigned(Primitive primitive);

    ///
    /// \param primitive Arbitrary primitive size
    /// \return Return true if primitive represents an integral type
    bool is_integer(Primitive primitive);

    ///
    /// \param primitive Arbitrary primitive size
    /// \return Return true if primitive represents a floating-point type
    bool is_floating_point(Primitive primitive);

    //=====================================================
    // as_primitve declaration & specializations
    //=====================================================

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

    //=====================================================
    // primitive_to_type declaration & specializations
    //=====================================================

    template<Primitive p>
    struct primitive_to_type;

    template<Primitive p>
    using primitive_to_type_t = typename primitive_to_type<p>::type;

    template<>
    struct primitive_to_type<Primitive::NULL_PRIMITIVE>{
        using type = void;
    };

    template<>
    struct primitive_to_type<Primitive::UINT8>{
        using type = std::uint8_t;
    };

    template<>
    struct primitive_to_type<Primitive::UINT16>{
        using type = std::uint16_t;
    };

    template<>
    struct primitive_to_type<Primitive::UINT32>{
        using type = std::uint32_t;
    };

    template<>
    struct primitive_to_type<Primitive::UINT64>{
        using type = std::uint64_t;
    };


    template<>
    struct primitive_to_type<Primitive::INT8>{
        using type = std::int8_t;
    };

    template<>
    struct primitive_to_type<Primitive::INT16>{
        using type = std::int16_t;
    };

    template<>
    struct primitive_to_type<Primitive::INT32>{
        using type = std::int32_t;
    };

    template<>
    struct primitive_to_type<Primitive::INT64>{
        using type = std::int64_t;
    };



    template<>
    struct primitive_to_type<Primitive::FLOAT16>{
        using type = half;
    };

    template<>
    struct primitive_to_type<Primitive::FLOAT32>{
        using type = float;
    };

    template<>
    struct primitive_to_type<Primitive::FLOAT64>{
        using type = double;
    };

}

#endif //AGS_CORE_TYPES_HPP
