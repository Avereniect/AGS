#include "Render_queue_kernel.hpp"

namespace ags::are::vk_kernel {

    //=====================================================
    // Static members
    //=====================================================

    vk::CommandPool Render_queue_kernel::pool{};

    //=====================================================
    // State functions
    //=====================================================

    void Render_queue_kernel::init() {
        auto graphics_queue_index = graphics_device.graphics_queue_index;

        vk::CommandPoolCreateInfo pool_create_info{
            vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
            graphics_queue_index
        };

        pool = graphics_device.handle.createCommandPool(pool_create_info);
    }

    void Render_queue_kernel::term() {
        graphics_device.handle.destroy(pool);
    }

    vk::CommandPool& Render_queue_kernel::command_pool() {
        return pool;
    }

}
