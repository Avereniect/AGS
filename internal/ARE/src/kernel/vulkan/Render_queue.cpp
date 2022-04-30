//
// Created by avereniect on 1/22/22.
//
#include "Render_queue.hpp"

namespace ags::are::vk10 {

    //=====================================================
    // -ctors
    //=====================================================

    //=====================================================
    // Assignment operators
    //=====================================================

    //Render_queue& Render_queue::operator=(Render_queue&&) noexcept;

    //=====================================================
    // Mutators
    //=====================================================

    void Render_queue::enqueue(
        const Mesh& mesh,
        const Shader_program& shader,
        const Framebuffer& framebuffers
    ) {
        vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, static_cast<vk::Pipeline>(shader));
        vkCmdDraw(command_buffer, mesh.vertex_count(), 1, 0, 0);

    }

}
