//
// Created by avereniect on 1/9/22.
//

#include "Kernel.hpp"
#include "Device_kernel.hpp"

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

namespace ags::are::vk10 {

    //=====================================================
    // State methods
    //=====================================================

    bool Kernel::init() {
        Kernel_base::init();
        Device_kernel::init();

        return true;
    }

    void Kernel::term() {
        Device_kernel::term();
        Kernel_base::term();
    }

}