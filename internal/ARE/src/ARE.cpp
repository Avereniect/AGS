//
// Created by avereniect on 1/9/22.
//

#include "ARE.hpp"

//#include "kernel/GL33/Kernel.hpp"

namespace ags::are {

    bool ARE::is_initialized = false;

    bool ARE::init() {
        if (is_initialized) {
            return false;
        }

        //gl33::Kernel::init();
        vk10::Kernel::init();

        is_initialized = true;
        return true;
    }

    void ARE::term() {
        if (!is_initialized) {
            return;
        }

        //gl33::Kernel::term();
        vk10::Kernel::term();

        is_initialized = false;
    }

}