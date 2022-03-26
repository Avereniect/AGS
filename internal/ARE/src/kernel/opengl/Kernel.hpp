//
// Created by avereniect on 1/1/22.
//

#ifndef AGS_GL43_KERNEL_HPP
#define AGS_GL43_KERNEL_HPP

#include "Mesh.hpp"
#include "Shader.hpp"
#include "Draw_call.hpp"

#include <cstdint>
#include <queue>

namespace ags::are::gl43 {
    ///
    /// Class wrapping around OpenGL 3.3 state
    ///
    class Kernel {
    public:

        //=================================================
        // State methods
        //=================================================

        static bool init();

        static void term();

        //=================================================
        // Drawing methods
        //=================================================

        ///
        /// Adds a draw call too internal queue.
        ///
        /// \param mesh Mesh to draw
        /// \param shader Shader to draw with
        static void queue_frame(const Mesh& mesh, const Shader& shader);

        ///
        /// Issues draw calls contained within queue
        ///
        static void draw_frame();

    private:

        static std::priority_queue<Draw_call> render_queue;

        //=================================================
        // Helper function
        //=================================================

        static void issue_draw_call(const Draw_call& draw_call);

    };

}

#endif //AGS_GL33_KERNEL_HPP
