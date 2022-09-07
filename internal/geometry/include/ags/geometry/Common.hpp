//
// Created by avereniect on 9/7/22.
//

#ifndef AGS_GEOMETRY_COMMON_HPP
#define AGS_GEOMETRY_COMMON_HPP

#include <avml/Vectors.hpp>
#include <avml/Matrices.hpp>

namespace ags::geometry {

    //=====================================================
    // Type aliases
    //=====================================================

    using real = float;
    using vec2r = avml::vec2f;
    using vec3r = avml::vec3f;
    using vec4r = avml::vec4f;

    using mat2x2 = avml::mat2x2f;
    using mat3x3 = avml::mat3x3f;
    using mat4x4 = avml::mat4x4f;

}

#endif //AGS_GEOMETRY_COMMON_HPP
