//
// Created by avereniect on 1/9/22.
//

#include "Kernel.hpp"
#include "Device_kernel.hpp"

namespace ags::are::vk_kernel {

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