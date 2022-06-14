//
// Created by avereniect on 12/22/21.
//

#ifndef AGS_APT_COMMON_HPP
#define AGS_APT_COMMON_HPP

//#define AVEL_AVX512VL
//#define AVEL_AVX512BW
#define AVEL_SSE2
#include "avel/Avel.hpp"

//#define AVML_AVX512VL
//#define AVML_AVX512BW
#define AVML_SSE2
#include "avml/AVML.hpp"

#include <ags/image/Pixel_buffer.hpp>

namespace ags::apt {

    //=====================================================
    // Types for scalar processing
    //=====================================================

    using uint32 = std::uint32_t;
    using int32 = std::int32_t;

    using uint64 = std::uint64_t;
    using int64 = std::int64_t;

    using vec2i = avml::Vector2I<int32>;
    using vec3i = avml::Vector3I<int32>;
    using vec4i = avml::Vector4I<int32>;

    using mat2x2i = avml::Matrix2x2R<int32>;
    using mat3x3i = avml::Matrix3x3R<int32>;
    using mat4x4i = avml::Matrix4x4R<int32>;


    using real = float;

    using uvec2r = avml::Unit_vector2R<real>;
    using uvec3r = avml::Unit_vector3R<real>;
    using uvec4r = avml::Unit_vector4R<real>;

    using vec2r = avml::Vector2R<real>;
    using vec3r = avml::Vector3R<real>;
    using vec4r = avml::Vector4R<real>;

    using mat2x2r = avml::Matrix2x2R<real>;
    using mat3x3r = avml::Matrix3x3R<real>;
    using mat4x4r = avml::Matrix4x4R<real>;

    using color = vec3r;

    //=====================================================
    // Types for vectorized processing
    //=====================================================

    ///
    /// How many elements are in vectorized processing
    ///
    static const int vector_width = avel::optimal_vector_width<float>::value;


    using int32v = avel::Vector<int32>;

    using vec2iv = avml::Vector2I<int32>;
    using vec3iv = avml::Vector3I<int32>;
    using vec4iv = avml::Vector4I<int32>;

    using mat2x2iv = avml::Matrix2x2R<int32>;
    using mat3x3iv = avml::Matrix3x3R<int32>;
    using mat4x4iv = avml::Matrix4x4R<int32>;


    using realv = avel::vec32f;

    using uvec2rv = avml::Unit_vector2R<realv>;
    using uvec3rv = avml::Unit_vector3R<realv>;
    using uvec4rv = avml::Unit_vector4R<realv>;

    using vec2rv = avml::Vector2R<realv>;
    using vec3rv = avml::Vector3R<realv>;
    using vec4rv = avml::Vector4R<realv>;

    using mat2x2rv = avml::Matrix2x2R<realv>;
    using mat3x3rv = avml::Matrix3x3R<realv>;
    using mat4x4rv = avml::Matrix4x4R<realv>;

    using colorv = vec3rv;

    //=====================================================
    // Image types
    //=====================================================

    using Image = ags::image::Pixel_buffer<float, 3>;

    //=====================================================
    // Image types
    //=====================================================

}

#endif //AGS_APT_COMMON_HPP
