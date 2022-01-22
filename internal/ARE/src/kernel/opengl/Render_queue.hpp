//
// Created by avereniect on 1/12/22.
//

#ifndef AGS_GL33_QUEUE_HPP
#define AGS_GL33_QUEUE_HPP

#include "Mesh.hpp"
#include "Shader.hpp"
#include <glad/glad.h>

#include <queue>
#include <cstdint>

namespace ags::are::gl33 {

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


    ///
    /// Render queue for OpenGL 3.3 ARE kernel.
    ///
    /// Resources that are used to enqueue a draw call should not be destroyed
    /// until the queue object has been submitted for rendering. This is not a
    /// concern if the queue is never submitted or if the queue is cleared
    /// before submitting however.
    ///
    class Render_queue {
    public:

        void queue_draw_call(const Mesh& mesh, const Shader& shader);

    private:

        std::priority_queue<Draw_call> queue{};

    };

}

#endif //AGS_GL33_QUEUE_HPP
