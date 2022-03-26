//
// Created by avereniect on 1/9/22.
//

#include "ARE.hpp"

#ifdef AGS_OPENGL43
#include "kernel/opengl/Kernel.hpp"
#endif

namespace ags::are {

    bool ARE::is_initialized = false;

    bool ARE::init() {
        if (is_initialized) {
            return false;
        }

        #if defined(AGS_VULKAN10)
        vk10::Kernel::init();
        #elif defined(AGS_OPENGL43)
        gl43::Kernel::init();
        #endif

        is_initialized = true;
        return true;
    }

    void ARE::term() {
        if (!is_initialized) {
            return;
        }

        #if defined(AGS_VULKAN10)
        vk10::Kernel::term();
        #elif defined(AGS_OPENGL43)
        gl43::Kernel::term();
        #endif

        is_initialized = false;
    }

}