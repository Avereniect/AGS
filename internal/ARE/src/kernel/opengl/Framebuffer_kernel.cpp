//
// Created by avereniect on 4/30/22.
//
#include "Framebuffer_kernel.hpp"

namespace ags::are::gl {

    const std::uint32_t framebuffer_reservation_size = 4;
    const std::uint32_t framebuffer_garbage_size = 4;

    void Framebuffer_kernel::init() {
        pool.reserve(framebuffer_reservation_size);
        garbage.reserve(framebuffer_garbage_size);
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

}
