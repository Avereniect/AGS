//
// Created by avereniect on 12/17/21.
//

#ifndef AGS_ARE_ARE_HPP
#define AGS_ARE_ARE_HPP

#include <cstdint>
#include <memory>

#include <avml/AVML.hpp>

#ifdef AGS_VULKAN
#include "kernel/vulkan/Kernel.hpp"
#include "kernel/vulkan/Mesh.hpp"
#include "kernel/vulkan/Texture.hpp"
#include "kernel/vulkan/Framebuffer.hpp"
#include "kernel/vulkan/Render_queue.hpp"

#endif

#ifdef AGS_OPENGL
#include "kernel/opengl/Kernel.hpp"

#include "kernel/opengl/Shader.hpp"
#include "kernel/opengl/Mesh.hpp"
#include "kernel/opengl/Texture.hpp"
#include "kernel/opengl/Framebuffer.hpp"

#include "kernel/opengl/Render_queue.hpp"

#endif

namespace ags::are {

    //=====================================================
    // Type aliases
    //=====================================================

    #ifdef AGS_VULKAN
    using Kernel = vk_kernel::Kernel;

    using Compute_shader = vk_kernel::Compute_shader;
    using Vertex_shader = vk_kernel::Vertex_shader;
    using Fragment_shader = vk_kernel::Fragment_shader;
    using Shader_program = vk_kernel::Shader_program;

    using Mesh = vk_kernel::Mesh;

    using Texture1D = vk_kernel::Texture1D;
    using Texture2D = vk_kernel::Texture2D;
    using Texture3D = vk_kernel::Texture3D;

    using Framebuffer = vk_kernel::Framebuffer;

    using Render_queue = vk_kernel::Render_queue;

    #endif

    #ifdef AGS_OPENGL
    using Kernel = ags::are::gl_kernel::Kernel;

    using Compute_shader  = ags::are::gl_kernel::Compute_shader;
    using Vertex_shader   = ags::are::gl_kernel::Vertex_shader;
    using Fragment_shader = ags::are::gl_kernel::Fragment_shader;
    using Shader_program  = ags::are::gl_kernel::Shader_program;

    using Mesh            = ags::are::gl_kernel::Mesh;

    using Texture1D       = ags::are::gl_kernel::Texture1D;
    using Texture2D       = ags::are::gl_kernel::Texture2D;
    using Texture3D       = ags::are::gl_kernel::Texture3D;

    using Framebuffer     = ags::are::gl_kernel::Framebuffer;

    using Render_queue    = ags::are::gl_kernel::Render_queue;

    #endif

    class ARE {
    public:

        ///
        /// \param api Enum indicating which API ARE should use
        /// \return True if ARE was initialized successfully. False otherwise
        static bool init();

        ///
        /// Terminates ARE. All resources are freed.
        ///
        static void term();

    private:

        //=================================================
        // Static members
        //=================================================

        static bool is_initialized;

    };

    void draw(
        Render_queue& queue,
        const vk_kernel::Window_data& window_data
    );

    ///
    /// \param queue
    /// \param framebuffer
    void draw(
        Render_queue& queue,
        Framebuffer& framebuffer
    );

}

#endif //AGS_ARE_ARE_HPP
