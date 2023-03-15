#include "Render_queue.hpp"

#include "Device_kernel.hpp"
#include "Render_queue_kernel.hpp"

#include <utility>

namespace ags::are::vk_kernel {

    //=====================================================
    // -ctors
    //=====================================================

    Render_queue::Render_queue(Render_queue&& queue) noexcept:
        command_buffer(std::exchange(queue.command_buffer, {VK_NULL_HANDLE})) {}

    Render_queue::~Render_queue() {
        command_buffer.reset();

        Device_kernel::get_graphics_device().handle.freeCommandBuffers(
            Render_queue_kernel::command_pool(),
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

    void Render_queue::queue_draw_call(
        const Framebuffer& framebuffer,
        const Mesh& mesh,
        const Shader_program& shader
    ) {
        if (!command_buffer) {
            auto device = Device_kernel::get_graphics_device().handle;

            vk::CommandBufferAllocateInfo allocate_info{
                Render_queue_kernel::command_pool(),
                vk::CommandBufferLevel::ePrimary,
                1
            };

            auto command_buffers = device.allocateCommandBuffers(allocate_info);
            command_buffer = command_buffers[0];
        }

        if (!is_recording) {
            vk::CommandBufferBeginInfo begin_info{
                vk::CommandBufferUsageFlagBits::eOneTimeSubmit
            };

            command_buffer.begin(begin_info);
            is_recording = true;
        }

        command_buffer.bindPipeline(
            vk::PipelineBindPoint::eGraphics,
            shader.native_handle()
        );



        vk::RenderPassBeginInfo render_pass_info{
            framebuffer.native_renderpass(),
            framebuffer.native_handle(),
            vk::Rect2D{},
            framebuffer.native_clear_values()
        };

        render_pass_info.renderArea.extent = vk::Extent2D{framebuffer.width(), framebuffer.height()},
        render_pass_info.renderArea.offset = vk::Offset2D{0, 0},


        command_buffer.beginRenderPass(render_pass_info, vk::SubpassContents::eInline);

        command_buffer.setViewport(
            0, //First viewport index
            {vk::Viewport(0.0f, 0.0f, framebuffer.width(), framebuffer.height(), 0.0, 1.0f)}
        );

        command_buffer.draw(
            mesh.vertex_count(),
            1,
            0,
            0
        );

        command_buffer.endRenderPass();
    }

    void Render_queue::prepare() {
        command_buffer.end();
        is_recording = false;
    }

    void Render_queue::clear() {
        //TODO: Implement
    }

    vk::CommandBuffer Render_queue::native_handle() const{
        return command_buffer;
    }

}
