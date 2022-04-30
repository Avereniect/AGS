//
// Created by avereniect on 1/22/22.
//

#ifndef AGS_ARE_VK10_RENDER_QUEUE_HPP
#define AGS_ARE_VK10_RENDER_QUEUE_HPP

#include "Draw_call.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Framebuffer.hpp"

#include <queue>

#include <vulkan/vulkan.hpp>

namespace ags::are::vk10 {

    class Render_queue {
    public:

        //=================================================
        // -ctors
        //=================================================

        Render_queue() = default;
        Render_queue(const Render_queue&) = delete;
        Render_queue(Render_queue&&) noexcept;
        ~Render_queue();

        //=================================================
        // Assignment operators
        //=================================================

        Render_queue& operator=(const Render_queue&) = delete;
        Render_queue& operator=(Render_queue&&) noexcept;

        //=================================================
        // Mutators
        //=================================================

        ///
        /// TODO: Add parameter that contains uniforms/alternatives
        ///
        /// \param mesh
        /// \param shader
        /// \param framebuffer
        void enqueue(
            const Mesh& mesh,
            const Shader_program& shader,
            const Framebuffer& framebuffer
        );

    private:

        //=================================================
        // Instance members
        //=================================================

        vk::CommandBuffer command_buffer;

    };

}

#endif //AGS_ARE_VK10_RENDER_QUEUE_HPP
