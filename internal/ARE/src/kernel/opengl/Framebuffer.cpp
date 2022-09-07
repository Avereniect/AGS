//
// Created by avereniect on 4/30/22.
//
#include "Framebuffer.hpp"
#include "Framebuffer_kernel.hpp"
#include "Texture_kernel.hpp"

#include <ags/Logging.hpp>

#include <utility>

namespace ags::are::gl_kernel {

    //=====================================================
    // -ctors
    //=====================================================

    Framebuffer::Framebuffer(Framebuffer&& framebuffer) noexcept:
        dims(std::exchange(framebuffer.dims, {0, 0})),
        color_attachment_descriptions(std::exchange(framebuffer.color_attachment_descriptions, {})),
        color_attachment_ids(std::exchange(framebuffer.color_attachment_ids, {})),
        depth_stencil_format(std::exchange(framebuffer.depth_stencil_format, {})),
        depth_stencil_attachment_id(std::exchange(framebuffer.depth_stencil_attachment_id, {})) {}

    Framebuffer::~Framebuffer() {
        remove_attachments();
    }

    //=====================================================
    // Assignment operators
    //=====================================================

    Framebuffer& Framebuffer::operator=(Framebuffer&& framebuffer) noexcept {
        dims = std::exchange(framebuffer.dims, {});
        color_attachment_descriptions = std::exchange(framebuffer.color_attachment_descriptions, {});
        color_attachment_ids = std::exchange(framebuffer.color_attachment_ids, {});
        depth_stencil_format = std::exchange(framebuffer.depth_stencil_format, {});
        depth_stencil_attachment_id = std::exchange(framebuffer.depth_stencil_attachment_id, {});

        return *this;
    }

    //=====================================================
    // Mutators
    //=====================================================

    void Framebuffer::specify_attachments(
        std::uint32_t w, std::uint32_t h,
        std::initializer_list<are::Color_attachment> color_attachments,
        Sample_count samples
    ) {
        specify_attachments(w, h, color_attachments, Depth_format::NULL_DEPTH_FORMAT, samples);
    }

    void Framebuffer::specify_attachments(
        std::uint32_t w, std::uint32_t h,
        std::initializer_list<are::Color_attachment> color_attachments,
        Depth_format format,
        Sample_count samples
    ) {
        specify_attachments(w, h, color_attachments, to_depth_stencil_format(format), samples);
    }

    void Framebuffer::specify_attachments(
        std::uint32_t w, std::uint32_t h,
        std::initializer_list<are::Color_attachment> color_attachments,
        Stencil_format format,
        Sample_count samples
    ) {
        specify_attachments(w, h, color_attachments, to_depth_stencil_format(format), samples);
    }

    void Framebuffer::specify_attachments(
        std::uint32_t w, std::uint32_t h,
        std::initializer_list<are::Color_attachment> color_attachments,
        Depth_stencil_format ds_format,
        Sample_count samples
    ) {
        if (id == 0) {
            id = Framebuffer_kernel::acquire_framebuffer();
        }

        glBindFramebuffer(GL_FRAMEBUFFER, id);

        sample_count = samples;
        dims = {w, h};

        //TODO: Add proper error handling and input validation
        //TODO: Check that w and h are within bounds.
        //TODO: Check that not too many color attachments were specified

        create_color_attachments(w, h, color_attachments);
        create_depth_stencil_attachments(w, h, ds_format);

        validate();
    }

    void Framebuffer::remove_attachments() {
        color_attachment_descriptions.clear();

        glDeleteTextures(color_attachment_ids.size(), color_attachment_ids.data());
        color_attachment_ids.clear();

        glDeleteTextures(1, &depth_stencil_attachment_id);
        depth_stencil_attachment_id = 0;
    }

    void Framebuffer::clear() {
        remove_attachments();

        glDeleteFramebuffers(1, &id); //TODO: Defer release of resources to kernel
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

    Sample_count Framebuffer::samples() const {
        return sample_count;
    }

    aul::Span<const ags::are::Color_attachment> Framebuffer::color_attachments() const {
        return {
            color_attachment_descriptions.data(),
            color_attachment_descriptions.size()
        };
    }

    aul::Span<const GLuint> Framebuffer::native_color_attachment_handles() const {
        return {
            color_attachment_ids.data(),
            color_attachment_ids.size()
        };
    }


    Depth_format Framebuffer::depth_attachment_format() const {
        return to_depth_format(depth_stencil_format);
    }

    Stencil_format Framebuffer::stencil_attachment_format() const {
        return to_stencil_format(depth_stencil_format);
    }

    Depth_stencil_format Framebuffer::depth_stencil_attachment_format() const {
        return depth_stencil_format;
    }

    //=====================================================
    // Helper functions
    //=====================================================

    void Framebuffer::validate() const {
        //#if defined(AGS_ARE_GL_DEBUG)

        glBindFramebuffer(GL_FRAMEBUFFER, id);
        auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

        if (status == GL_FRAMEBUFFER_COMPLETE) {
            return;
        }

        //TODO: Refactor this so that it's less repetitive
        switch (status) {
        case GL_FRAMEBUFFER_UNDEFINED:
            AGS_ERROR(
                "Error detected while validating "
                "framebuffer. Framebuffer status is GL_FRAMEBUFFER_UNDEFINED"
            ); return;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            AGS_ERROR(
                "Error detected while validating "
                "framebuffer. Framebuffer status is "
                "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT"
            ); return;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            AGS_ERROR(
                "Error detected while validating "
                "framebuffer. Framebuffer status is "
                "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT"
            ); return;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            AGS_ERROR(
                "Error detected while validating "
                "framebuffer. Framebuffer status is "
                "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER"
            ); return;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            AGS_ERROR(
                "Error detected while validating "
                "framebuffer. Framebuffer status is "
                "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER"
            ); return;
        case GL_FRAMEBUFFER_UNSUPPORTED:
            AGS_ERROR(
                "Error detected while validating "
                "framebuffer. Framebuffer status is "
                "GL_FRAMEBUFFER_UNSUPPORTED"
            ); return;
        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
            AGS_ERROR(
                "Error detected while validating "
                "framebuffer. Framebuffer status is "
                "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE"
            ); return;
        case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
            AGS_ERROR(
                "Error detected while validating "
                "framebuffer. Framebuffer status is "
                "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS"
            ); return;
        default:
            AGS_ERROR(
                "Error detected while validating "
                "framebuffer. Unrecognized framebuffer status"
            ); return;
        }

        int breakpoint_dummy = 10;

        //#endif
    }

    void Framebuffer::create_color_attachments(
        std::uint32_t w, std::uint32_t h,
        std::initializer_list<are::Color_attachment> color_attachments
    ) {
        //Create attachment descriptions
        color_attachment_descriptions.resize(color_attachments.size());
        for (std::size_t i = 0; i < color_attachments.size(); ++i) {
            color_attachment_descriptions[i].format = color_attachments.begin()[i].format;
            color_attachment_descriptions[i].type = color_attachments.begin()[i].type;
        }

        //Retrieve color attachment ids
        color_attachment_ids.resize(color_attachment_descriptions.size());
        for (auto& id : color_attachment_ids) {
            id = Texture_kernel::acquire_texture();
        }

        //Create color attachments
        for (std::size_t i = 0; i < color_attachments.size(); ++i) {
            const Color_attachment& desc = color_attachment_descriptions[i];

            auto format = desc.format;

            auto channel_type = desc.type;

            color_attachment_ids[i] = Texture_kernel::acquire_texture();

            glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, color_attachment_ids[i]);

            glTexImage2DMultisample(
                GL_TEXTURE_2D_MULTISAMPLE,
                static_cast<GLint>(sample_count),
                to_native_enum(format, channel_type),
                GLsizei(dims[0]), GLsizei(dims[1]),
                true
            );

            glFramebufferTexture2D(
                GL_FRAMEBUFFER,
                GL_COLOR_ATTACHMENT0 + i,
                GL_TEXTURE_2D_MULTISAMPLE,
                color_attachment_ids[i],
                0 //Mipmap level
            );
        }
    }

    void Framebuffer::create_depth_stencil_attachments(
        std::uint32_t w, std::uint32_t h,
        ags::are::Depth_stencil_format ds_format
    ) {
        GLenum native_enum = to_native_enum(ds_format);

        //Create depth-stencil attachment
        if (ds_format != Depth_stencil_format::NULL_DEPTH_STENCIL_FORMAT) {
            depth_stencil_attachment_id = Texture_kernel::acquire_texture();

            glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, depth_stencil_attachment_id);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            /*
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                to_internal_format(ds_format),
                GLsizei(w), GLsizei(h),
                0, //Border. Required to be 0
                to_format(ds_format),
                to_type(ds_format),
                nullptr
            );
            */

            glTexImage2DMultisample(
                GL_TEXTURE_2D_MULTISAMPLE,
                static_cast<GLint>(sample_count),
                to_internal_format(ds_format),
                GLsizei(w), GLsizei(h),
                true
            );

            glFramebufferTexture2D(
                GL_FRAMEBUFFER,
                to_attachment_point(ds_format),
                GL_TEXTURE_2D_MULTISAMPLE,
                depth_stencil_attachment_id,
                0 //Mipmap level
            );
        }
    }

    GLenum Framebuffer::to_attachment_point(Depth_stencil_format format) {
        if (is_combined_format(format)) {
            return GL_DEPTH_STENCIL_ATTACHMENT;
        } else if (to_stencil_format(format) != Stencil_format::NULL_STENCIL_FORMAT) {
            return GL_STENCIL_ATTACHMENT;
        } else if (to_depth_format(format) != Depth_format::NULL_DEPTH_FORMAT) {
            return GL_DEPTH_ATTACHMENT;
        } else {
            return GLenum{};
        }
    }

    GLint Framebuffer::to_internal_format(ags::are::Depth_stencil_format format) {
        switch (format) {
        case Depth_stencil_format::INT24: return GL_DEPTH_COMPONENT24;
        case Depth_stencil_format::FLOAT32: return GL_DEPTH_COMPONENT32F;
        case Depth_stencil_format::STENCIL8: return GL_STENCIL_INDEX8;
        case Depth_stencil_format::INT24_STENCIL8: return GL_DEPTH24_STENCIL8;
        case Depth_stencil_format::FLOAT32_STENCIL8: return GL_DEPTH32F_STENCIL8;
        default: return 0;
        }
    }

    /*
    GLenum Framebuffer::to_format(Depth_stencil_format format) {
        switch (format) {
        case Depth_stencil_format::INT24: return GL_DEPTH_COMPONENT;
        case Depth_stencil_format::FLOAT32: return GL_DEPTH_COMPONENT;
        case Depth_stencil_format::STENCIL8: return GL_STENCIL_INDEX;
        case Depth_stencil_format::INT24_STENCIL8: return GL_DEPTH_STENCIL;
        case Depth_stencil_format::FLOAT32_STENCIL8: return GL_DEPTH_STENCIL;
        default: return 0;
        }
    }

    GLenum Framebuffer::to_type(Depth_stencil_format format) {
        switch (format) {
        case Depth_stencil_format::INT24: return GL_UNSIGNED_INT;
        case Depth_stencil_format::FLOAT32: return GL_FLOAT;
        case Depth_stencil_format::STENCIL8: return GL_UNSIGNED_BYTE;
        case Depth_stencil_format::INT24_STENCIL8: return GL_UNSIGNED_INT_24_8;
        case Depth_stencil_format::FLOAT32_STENCIL8: return GL_FLOAT_32_UNSIGNED_INT_24_8_REV;
        default: return 0;
        }
    }
    */

}
