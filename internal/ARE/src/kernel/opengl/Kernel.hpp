//
// Created by avereniect on 1/1/22.
//

#ifndef AGS_ARE_GL_KERNEL_HPP
#define AGS_ARE_GL_KERNEL_HPP

#include "Render_queue.hpp"
#include "Compute_queue.hpp"

#include "Mesh_kernel.hpp"
#include "Texture_kernel.hpp"
#include "Shader_kernel.hpp"
#include "Framebuffer_kernel.hpp"

#include <cstdint>
#include <queue>
#include <array>

namespace ags::are::gl_kernel {

    ///
    /// Class wrapping around OpenGL rendering context.
    ///
    /// Public-facing
    ///
    class Kernel :
        public Mesh_kernel,
        public Texture_kernel,
        public Shader_kernel,
        public Framebuffer_kernel {
    public:

        //=================================================
        // State methods
        //=================================================

        ///
        ///
        ///
        static void init();

        ///
        ///
        ///
        static void term();

        //=================================================
        // State mutators
        //=================================================

        //=================================================
        // Drawing methods
        //=================================================

        ///
        /// Submit the work contains within the specified render queue. Function
        /// may return before the commands are completed.
        ///
        /// Note: Contents of render queue may be sorted during this submission
        ///
        /// \param render_queue Queue containing draw calls
        static void submit_render_queue(
            Render_queue& render_queue,
            GLuint framebuffer_id,
            attachment_mask_type attachment_mask,
            std::array<std::uint32_t, 2> dims
        );

        ///
        ///
        /// \param compute_queue Queue containing compute tasks to execute
        static void submit_compute_queue(Compute_queue& compute_queue);

    };

}

#endif //AGS_ARE_GL_KERNEL_HPP
