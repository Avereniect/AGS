//
// Created by avereniect on 1/24/22.
//

#ifndef AGS_GL43_DRAW_CALL_HPP
#define AGS_GL43_DRAW_CALL_HPP

namespace ags::are::gl43 {

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

            if (ebo < rhs.ebo) {
                return true;
            }

            if (framebuffer < rhs.framebuffer) {
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

        std::uint32_t num_elements = 0;
        GLuint ebo = 0;

        GLuint shader = 0;
        GLuint framebuffer = 0;
    };

}

#endif //AGS_GL33_DRAW_CALL_HPP
