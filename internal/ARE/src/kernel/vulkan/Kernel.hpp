#ifndef AGS_ARE_VK_KERNEL_HPP
#define AGS_ARE_VK_KERNEL_HPP

#include <ags/Graphics_includes.hpp>

#include "Kernel_base.hpp"
#include "Device_kernel.hpp"
#include "Shader_kernel.hpp"
#include "Framebuffer_kernel.hpp"
#include "Mesh_kernel.hpp"
#include "Memory_kernel.hpp"
#include "Texture_kernel.hpp"
#include "Render_queue_kernel.hpp"

#include "Render_queue.hpp"

#include <vector>
#include <string>

namespace ags::are::vk_kernel {

    class Kernel :
        public Shader_kernel,
        public Mesh_kernel,
        public Framebuffer_kernel,
        public Texture_kernel,
        public Render_queue_kernel {
    public:

        //TODO: Move to framebuffer kernel
        using attachment_mask_type = std::uint8_t;

        //=================================================
        // State methods
        //=================================================

        static bool init();
        static void term();

        //=================================================
        // Draw methods
        //=================================================

        static void submit_render_queue(
            Render_queue& queue,
            vk::Framebuffer,
            attachment_mask_type m,
            std::array<std::uint32_t, 2> dimensions
        );

    private:

        //=================================================
        // Static members
        //=================================================

        static vk::Fence command_fence;

        //=================================================
        // Helper functions
        //=================================================

    };

    struct Window_data{
        const vk::Semaphore& swapchain_semaphore;
    };

}

#endif //AGS_ARE_VK_KERNEL_HPP
