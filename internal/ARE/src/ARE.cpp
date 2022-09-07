//
// Created by avereniect on 1/9/22.
//

#include "ARE.hpp"

#ifdef AGS_OPENGL
#include "kernel/opengl/Kernel.hpp"
#endif

#ifdef AGS_VULKAN
#include "kernel/vulkan/Kernel.hpp"
#endif

namespace ags::are {

    //=====================================================
    // Static members
    //=====================================================

    bool ARE::is_initialized = false;

    //=====================================================
    // State functions
    //=====================================================

    bool ARE::init() {
        if (is_initialized) {
            return false;
        }

        Kernel::init();

        is_initialized = true;
        return true;
    }

    void ARE::term() {
        if (!is_initialized) {
            return;
        }

        Kernel::term();

        is_initialized = false;
    }

    //=====================================================
    // Misc. Functions
    //=====================================================

    void draw(
        Render_queue& queue,
        Framebuffer& framebuffer
    ) {
        auto attachment_count = framebuffer.color_attachments().size();
        Kernel::attachment_mask_type attachment_mask = (1 << attachment_count) - 1;
        Kernel::submit_render_queue(queue, framebuffer.native_handle(), attachment_mask, framebuffer.dimensions());
    }

}
