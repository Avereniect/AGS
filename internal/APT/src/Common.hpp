//
// Created by avereniect on 12/22/21.
//

#ifndef AGS_COMMON_HPP
#define AGS_COMMON_HPP

#define AVEL_AVX512VL
#define AVEL_AVX512BW
#include "avel/Avel.hpp"

#define AVML_AVX512VL
#define AVML_AVX512BW
#include "avml/AVML.hpp"

#include <ags/image/Pixel_buffer.hpp>

namespace ags::apt {

    //=====================================================
    // Types for scalar processing
    //=====================================================

    using whole = std::int32_t;

    using vec2w = avml::Vector2I<whole>;
    using vec3w = avml::Vector3I<whole>;
    using vec4w = avml::Vector4I<whole>;

    using mat2x2w = avml::Matrix2x2R<whole>;
    using mat3x3w = avml::Matrix3x3R<whole>;
    using mat4x4w = avml::Matrix4x4R<whole>;


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


    using wholev = avel::Vector<whole>;

    using vec2wv = avml::Vector2I<wholev>;
    using vec3wv = avml::Vector3I<wholev>;
    using vec4wv = avml::Vector4I<wholev>;

    using mat2x2wv = avml::Matrix2x2R<wholev>;
    using mat3x3wv = avml::Matrix3x3R<wholev>;
    using mat4x4wv = avml::Matrix4x4R<wholev>;


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
    // Render setting types
    //=====================================================

    enum class Pixel_filer {
        BOX,
        GAUSSIAN
    };

}

#endif //AGS_COMMON_HPP
