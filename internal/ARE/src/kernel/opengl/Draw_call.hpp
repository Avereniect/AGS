//
// Created by avereniect on 1/24/22.
//

#ifndef AGS_ARE_GL_DRAW_CALL_HPP
#define AGS_ARE_GL_DRAW_CALL_HPP

#include <ags/Graphics_includes.hpp>

#include "Framebuffer_kernel.hpp"

#include <cstdint>

namespace ags::are::gl_kernel {

    struct Draw_call {

        //=================================================
        // Comparison operators
        //=================================================

        bool operator<(const Draw_call& rhs) const {
            // Order should be:
            // Uniforms
            // Mesh
            // Framebuffer
            // Shaders
            //TODO: Take into consideration depth. Fiddle with order to
            // determine best place to perform comparison

            if (vao < rhs.vao) {
                return true;
            }

            if (shader < rhs.shader) {
                return true;
            }

            return false;
        }

        //=================================================
        // Instance members
        //=================================================

        std::uint32_t num_indices = 0;
        GLuint vao = 0;
        GLuint shader = 0;

    };

}

#endif //AGS_ARE_GL_DRAW_CALL_HPP
