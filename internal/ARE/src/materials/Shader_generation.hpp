//
// Created by avereniect on 6/30/22.
//

#ifndef AGS_SHADER_GENERATION_HPP
#define AGS_SHADER_GENERATION_HPP

#include <tuple>
#include <string>

#include "Node_tree.hpp"

namespace ags::are {

    const std::string_view lambertian_diffuse_path = "./assets/shader_fragments/lambertian_diffuse.txt";
    const std::string_view ambient_diffuse_path = "./assets/shader_fragments/ambient.txt";
    const std::string_view phong_specular_path = "./assets/shader_fragments/phong_specular.txt";

    ///
    /// \param tree Note tree to generate GLSL source code for
    /// \return Pair of strings containing GLSL vertex and fragment shader
    /// source code for the input node tree
    std::pair<std::string, std::string> generate_glsl_shaders(const Node_tree& tree);

}

#endif //AGS_SHADER_GENERATION_HPP
