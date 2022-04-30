//
// Created by avereniect on 1/12/22.
//

#ifndef AGS_GL43_QUEUE_HPP
#define AGS_GL43_QUEUE_HPP

#include "Includes.hpp"

#include "Draw_call.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Framebuffer.hpp"
#include "Uniform_pack.hpp"

#include <queue>
#include <cstdint>

namespace ags::are::gl43 {

    ///
    /// Render queue for OpenGL 4.3 ARE kernel.
    ///
    /// Resources that are used to enqueue a draw call should not be destroyed
    /// until the queue object has been submitted for rendering. This is not a
    /// concern if the queue is never submitted or if the queue is cleared
    /// before submitting however.
    ///
    class Render_queue {
    public:

        //=================================================
        // -ctors
        //=================================================

        //=================================================
        // Mutators
        //=================================================

        void queue_draw_call(
            const Mesh& mesh,
            const Shader& shader,
            const Framebuffer& framebuffer
        );

    private:

        std::priority_queue<Draw_call> queue{};

    };

}

#endif //AGS_GL43_QUEUE_HPP
