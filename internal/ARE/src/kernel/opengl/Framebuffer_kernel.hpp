//
// Created by avereniect on 4/30/22.
//

#ifndef AGS_FRAMEBUFFER_KERNEL_HPP
#define AGS_FRAMEBUFFER_KERNEL_HPP

#include <ags/Graphics_includes.hpp>

#include "Kernel_base.hpp"

#include <vector>

namespace ags::are::gl_kernel {

    class Framebuffer_kernel : public Kernel_base {
    public:

        //=================================================
        // Type aliases
        //=================================================


        ///
        /// As of Aug. 2022, gpuinfo.org reports that the max number of color
        /// attachments on any device, across both OpenGL and Vulkan is only 8
        using attachment_mask_type = std::uint8_t;

        //=================================================
        // Initialization
        //=================================================

        static void init();
        static void term();

        //=================================================
        // State mutators
        //=================================================

        static GLuint acquire_framebuffer();
        static void release_framebuffer(GLuint);

        static void clean_up();

        static void activate_color_attachments(attachment_mask_type mask);

        //=================================================
        // Queries
        //=================================================

        [[nodiscard]]
        static std::uint32_t max_framebuffer_color_attachments();

    private:

        //=================================================
        // Static members
        //=================================================

        ///
        ///
        ///
        static std::vector<GLuint> pool;

        ///
        ///
        ///
        static std::vector<GLuint> garbage;

        ///
        ///
        ///
        static std::vector<GLenum> active_color_attachment_enums;

    };

}

#endif //AGS_FRAMEBUFFER_KERNEL_HPP
