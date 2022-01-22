//
// Created by avereniect on 1/12/22.
//

#ifndef AGS_GL33_SHADER_HPP
#define AGS_GL33_SHADER_HPP

#include "Object.hpp"
#include <glad/glad.h>

#include <string>

namespace ags::are::gl33 {

    class Shader : public Object {
    public:

        void load(const std::string& vertex_src, const std::string& fragment_src);

    private:

        //=================================================
        // Helper functions
        //=================================================

        void compile_vertex_shader() {

        }

        void compile_fragment_shader() {

        }

    };

}

#endif //AGS_GL33_SHADER_HPP
