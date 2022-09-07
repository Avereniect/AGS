//
// Created by avereniect on 4/30/22.
//
#include "Framebuffer_kernel.hpp"

#include <climits>

namespace ags::are::gl_kernel {

    //=====================================================
    // Type aliases
    //=====================================================

    using attachment_mask_type = Framebuffer_kernel::attachment_mask_type;

    //=====================================================
    // Static members
    //=====================================================

    std::vector<GLuint> Framebuffer_kernel::pool{};
    std::vector<GLuint> Framebuffer_kernel::garbage{};

    std::vector<GLenum> Framebuffer_kernel::active_color_attachment_enums;

    const std::uint32_t framebuffer_reservation_size = 4;
    const std::uint32_t framebuffer_garbage_size = 4;

    //=====================================================
    // Initialization
    //=====================================================

    void Framebuffer_kernel::init() {
        pool.reserve(framebuffer_reservation_size);
        garbage.reserve(framebuffer_garbage_size);

        active_color_attachment_enums.reserve(max_framebuffer_color_attachments());
    }

    void Framebuffer_kernel::term() {
        clean_up();

        //Release handles in pool
        glDeleteFramebuffers(pool.size(), pool.data());
    }

    //=====================================================
    // State mutators
    //=====================================================

    GLuint Framebuffer_kernel::acquire_framebuffer() {
        if (pool.empty()) {
            pool.resize(framebuffer_reservation_size);
            glGenFramebuffers(framebuffer_reservation_size, pool.data());
        }

        auto ret = pool.back();
        pool.pop_back();
        return ret;
    }

    void Framebuffer_kernel::release_framebuffer(GLuint id) {
        if (garbage.size()) {

        }
        garbage.emplace_back(id);
    }

    void Framebuffer_kernel::clean_up() {
        glDeleteFramebuffers(garbage.size(), garbage.data());
    }

    void Framebuffer_kernel::activate_color_attachments(attachment_mask_type mask) {
        active_color_attachment_enums.clear();
        const auto iterations = sizeof(attachment_mask_type) * CHAR_BIT;
        for (int i = 0; i < iterations; ++i) {
            if ((1 << i) & mask) {
                active_color_attachment_enums.push_back(GL_COLOR_ATTACHMENT0 + i);
            }
        }

        glDrawBuffers(
            active_color_attachment_enums.size(),
            active_color_attachment_enums.data()
        );
    }

    //=====================================================
    // Queries
    //=====================================================

    std::uint32_t Framebuffer_kernel::max_framebuffer_color_attachments() {
        GLint ret;
        glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &ret);
        return ret;
    }

}
