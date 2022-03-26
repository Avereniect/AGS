//
// Created by avereniect on 1/22/22.
//
#include "Render_queue.hpp"

namespace ags::are::vk10 {

    void Render_queue::draw(
            const Mesh& mesh,
            const Shader& shader,
            const Framebuffer& framebuffer
    ) {
        vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, static_cast<vk::Pipeline>(shader));
        vkCmdDraw(command_buffer, mesh.vertex_count, 1, 0, 0);
    }


}
