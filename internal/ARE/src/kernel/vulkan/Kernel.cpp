//
// Created by avereniect on 1/9/22.
//

#include "Kernel.hpp"

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

namespace ags::are::vk10 {

    bool Kernel::init() {
        Kernel_base::init();

        return true;
    }

    void Kernel::term() {
        Kernel_base::term();
    }

}