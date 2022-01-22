//
// Created by avereniect on 1/13/22.
//

#ifndef AGS_VK10_KERNEL_BASE_HPP
#define AGS_VK10_KERNEL_BASE_HPP

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

namespace ags::are::vk10 {

    class Kernel_base {
    public:

        //=================================================
        // State methods
        //=================================================

        static bool init();
        static void term();

    protected:

        //=================================================
        // Static members
        //=================================================

        static VkInstance instance;

    private:

        //=================================================
        // Helper functions
        //=================================================

    };

}

#endif //AGS_VK10_KERNEL_BASE_HPP
