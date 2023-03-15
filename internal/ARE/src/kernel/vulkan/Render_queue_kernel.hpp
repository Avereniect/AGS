#ifndef AGS_ARE_VK_RENDER_QUEUE_KERNEL_HPP
#define AGS_ARE_VK_RENDER_QUEUE_KERNEL_HPP

#include "Memory_kernel.hpp"

namespace ags::are::vk_kernel {

    class Render_queue_kernel : public Memory_kernel {
    public:

        //=================================================
        // State functions
        //=================================================

        static void init();

        static void term();

        //=================================================
        // Accessors
        //=================================================

        [[nodiscard]]
        static vk::CommandPool& command_pool();

    private:

        //=================================================
        // Static members
        //=================================================

        ///
        /// TODO: Replace with more nuanced approach
        ///
        static vk::CommandPool pool;

    };

}

#endif //AGS_ARE_VK_RENDER_QUEUE_KERNEL_HPP
