//
// Created by avereniect on 1/22/22.
//
#include "Render_queue.hpp"

#include "Device_kernel.hpp"

#include <utility>

namespace ags::are::vk_kernel {

    //=====================================================
    // -ctors
    //=====================================================

    Render_queue::Render_queue(Render_queue&& queue) noexcept:
        command_buffer(std::exchange(queue.command_buffer, {VK_NULL_HANDLE})) {}

    Render_queue::~Render_queue() {
        Device_kernel::get_graphics_device().handle.freeCommandBuffers(
            command_pool, //TODO: Actually select which command pool to use
            1,
            &command_buffer
        );
        //TODO: Release command buffer resource
    }

    //=====================================================
    // Assignment operators
    //=====================================================

    Render_queue& Render_queue::operator=(Render_queue&& rhs) noexcept {
        command_buffer = std::exchange(rhs.command_buffer, {VK_NULL_HANDLE});

        return *this;
    }

    //=====================================================
    // Mutators
    //=====================================================

    void Render_queue::enqueue(
        const Mesh& mesh,
        const Shader_program& shader,
        const Framebuffer& framebuffers
    ) {
        if (!command_buffer) {
            //TODO: Acquire
        }

        vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, static_cast<vk::Pipeline>(shader));
        vkCmdDraw(command_buffer, mesh.vertex_count(), 1, 0, 0);


    }

}
