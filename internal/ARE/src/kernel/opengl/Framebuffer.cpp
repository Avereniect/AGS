//
// Created by avereniect on 4/30/22.
//
#include "Framebuffer.hpp"

namespace ags::are::gl43 {

    //=====================================================
    // -ctors
    //=====================================================

    Framebuffer::~Framebuffer() {
        unload();
    }

    //=====================================================
    // Assignment operators
    //=====================================================

    //=====================================================
    // Mutators
    //=====================================================

    void Framebuffer::create_buffer(
        std::uint32_t w, std::uint32_t h,
        std::initializer_list<Color_attachment> color_attachments
    ) {
        create_buffer(w, h, color_attachments, Depth_format::NULL_DEPTH_FORMAT);
    }

    void Framebuffer::create_buffer(
        std::uint32_t w, std::uint32_t h,
        std::initializer_list<Color_attachment> color_attachments,
        Depth_format format
    ) {
        create_buffer(w, h, color_attachments, to_depth_stencil_format(format));
    }

    void Framebuffer::create_buffer(
        std::uint32_t w, std::uint32_t h,
        std::initializer_list<Color_attachment> color_attachments,
        Stencil_format format
    ) {
        create_buffer(w, h, color_attachments, to_depth_stencil_format(format));
    }

    void Framebuffer::create_buffer(
        std::uint32_t w, std::uint32_t h,
        std::initializer_list<Color_attachment> color_attachments,
        Depth_stencil_format format
    ) {
        if (id) {
            //TODO: Release resource to kernel instead
            glDeleteFramebuffers(1, &id);
        }

        glCreateFramebuffers(1, &id);

        gl
    }

    //=====================================================
    // Accessors
    //=====================================================

    std::array<std::uint32_t, 2> Framebuffer::dimensions() const {
        return dims;
    }

    std::uint32_t Framebuffer::width() const {
        return dims[0];
    }

    std::uint32_t Framebuffer::height() const {
        return dims[1];
    }

    //=====================================================
    // Helper functions
    //=====================================================

    void Framebuffer::verify() const {

    }

}
