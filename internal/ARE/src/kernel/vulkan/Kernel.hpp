//
// Created by avereniect on 1/9/22.
//

#ifndef AGS_ARE_VK_KERNEL_HPP
#define AGS_ARE_VK_KERNEL_HPP

#include <ags/Graphics_includes.hpp>

#include "Kernel_base.hpp"
#include "Device_kernel.hpp"

#include <vector>
#include <string>

namespace ags::are::vk_kernel {

    class Kernel :
        public Device_kernel {
    public:

        //=================================================
        // State methods
        //=================================================

        static bool init();
        static void term();

        //=================================================
        // Draw methods
        //=================================================

        void draw();

    private:

        //=================================================
        // Instance members
        //=================================================

        //=================================================
        // Helper functions
        //=================================================



    };

}

#endif //AGS_ARE_VK_KERNEL_HPP
