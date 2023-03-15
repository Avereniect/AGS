#include "Kernel.hpp"
#include "Device_kernel.hpp"

namespace ags::are::vk_kernel {

    //=====================================================
    // Static members
    //=====================================================

    vk::Fence Kernel::command_fence{};

    //=====================================================
    // State methods
    //=====================================================

    bool Kernel::init() {
        Kernel_base::init();
        Device_kernel::init();
        Memory_kernel::init();
        Mesh_kernel::init();
        Texture_kernel::init();
        Shader_kernel::init();
        Framebuffer_kernel::init();
        Render_queue_kernel::init();

        vk::FenceCreateInfo fence_create_info{
            vk::FenceCreateFlags{}
        };

        auto success = graphics_device.handle.createFence(&fence_create_info, nullptr, &command_fence);
        if (success != vk::Result::eSuccess) {
            AGS_FATAL("Failed to create fence in initialization of ");
            exit(EXIT_FAILURE);
        }

        return true;
    }

    void Kernel::term() {
        Render_queue_kernel::term();
        Framebuffer_kernel::term();
        Shader_kernel::term();
        Texture_kernel::term();
        Mesh_kernel::term();
        Memory_kernel::term();
        Device_kernel::term();
        Kernel_base::term();
    }

    void Kernel::submit_render_queue(
        Render_queue& queue,
        vk::Framebuffer framebuffer,
        attachment_mask_type m,
        std::array<std::uint32_t, 2> dimensions
    ) {
        queue.prepare();

        std::array<vk::CommandBuffer, 1> command_buffers{queue.native_handle()};

        //TODO: Pass semaphores that can be waited on
        vk::SubmitInfo submission_info{
            {},
            {},
            command_buffers
        };

        graphics_device.graphics_queue.submit({submission_info}, command_fence);

        auto result = graphics_device.handle.waitForFences({command_fence}, VK_TRUE, UINT64_MAX);
        if (result != vk::Result::eSuccess) {
            AGS_ERROR("Error while waiting for fence when submitting render queue");
        }

        graphics_device.handle.resetFences({command_fence});
    }

}
