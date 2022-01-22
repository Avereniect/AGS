//
// Created by avereniect on 1/9/22.
//

#ifndef AGS_VK10_KERNEL_HPP
#define AGS_VK10_KERNEL_HPP

#include "Kernel_base.hpp"

#include <vulkan/vulkan.h>

#include <vector>
#include <string>

namespace ags::are::vk10 {

    class Kernel {
    public:

        //=================================================
        // -ctors
        //=================================================

        static bool init();
        static void term();

        //=================================================
        // Assignment operators
        //=================================================

    private:

        //=================================================
        // Instance members
        //=================================================

        //=================================================
        // Helper functions
        //=================================================



    };

}

#endif //AGS_VK10_KERNEL_HPP
