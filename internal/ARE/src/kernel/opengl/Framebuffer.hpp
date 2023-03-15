#ifndef AGS_ARE_GL_FRAMEBUFFER_HPP
#define AGS_ARE_GL_FRAMEBUFFER_HPP

#include <ags/Graphics_includes.hpp>

#include "Object.hpp"
#include "Enums.hpp"
#include "../Framebuffer_common.hpp"

#include <aul/Span.hpp>

#include <cstdint>
#include <array>

namespace ags::are::gl_kernel {

    struct Depth_stencil_attachment {
        GLuint id = 0;
        Depth_stencil_format format = Depth_stencil_format::NULL_DEPTH_STENCIL_FORMAT;
    };

    struct Stencil_attachment {
        GLuint id = 0;
        Stencil_format format = Stencil_format::NULL_STENCIL_FORMAT;
    };



    class Framebuffer : public Object {
    public:

        //=================================================
        // -ctors
        //=================================================

        Framebuffer() = default;
        Framebuffer(const Framebuffer&) = delete;
        Framebuffer(Framebuffer&&) noexcept;
        ~Framebuffer();

        //=================================================
        // Assignment operators
        //=================================================

        Framebuffer& operator=(const Framebuffer&) = delete;
        Framebuffer& operator=(Framebuffer&&) noexcept;

        //=================================================
        // Mutators
        //=================================================

        void specify_attachments(
            std::uint32_t w, std::uint32_t h,
            std::initializer_list<are::Color_attachment> color_attachments,
            Sample_count samples = Sample_count::S1
        );

        void specify_attachments(
            std::uint32_t w, std::uint32_t h,
            std::initializer_list<are::Color_attachment> color_attachments,
            Depth_format depth_format,
            Sample_count samples = Sample_count::S1
        );

        void specify_attachments(
            std::uint32_t w, std::uint32_t h,
            std::initializer_list<are::Color_attachment> color_attachments,
            Stencil_format stencil_format,
            Sample_count samples = Sample_count::S1
        );

        void specify_attachments(
            std::uint32_t w, std::uint32_t h,
            std::initializer_list<are::Color_attachment> color_attachments,
            Depth_format depth_format,
            Stencil_format stencil_format,
            Sample_count samples = Sample_count::S1
        );

        void specify_attachments(
            std::uint32_t w, std::uint32_t h,
            std::initializer_list<are::Color_attachment> color_attachments,
            Depth_stencil_format depth_stencil_format,
            Sample_count samples = Sample_count::S1
        );

        ///
        /// Release framebuffer attachments resources
        ///
        void remove_attachments();

        ///
        /// Release held framebuffer resource
        ///
        void clear();

        //=================================================
        // Accessors
        //=================================================

        [[nodiscard]]
        std::array<std::uint32_t, 2> dimensions() const;

        [[nodiscard]]
        std::uint32_t width() const;

        [[nodiscard]]
        std::uint32_t height() const;


        [[nodiscard]]
        Sample_count samples() const;


        [[nodiscard]]
        aul::Span<const are::Color_attachment> color_attachments() const;

        [[nodiscard]]
        aul::Span<const GLuint> native_color_attachment_handles() const;


        [[nodiscard]]
        Depth_format depth_attachment_format() const;

        [[nodiscard]]
        Stencil_format stencil_attachment_format() const;

        [[nodiscard]]
        Depth_stencil_format depth_stencil_attachment_format() const;

    private:

        //=================================================
        // Instance members
        //=================================================

        ///
        /// Array containing dimensions of the frame buffer
        ///
        std::array<std::uint32_t, 2> dims{0, 0};

        ///
        /// Enum indicating number samples that attachments have
        ///
        Sample_count sample_count = Sample_count::S1;

        ///
        ///
        ///
        std::vector<Color_attachment> color_attachment_descriptions;

        ///
        ///
        ///
        std::vector<GLuint> color_attachment_ids;

        ///
        ///
        ///
        Depth_stencil_format depth_stencil_format = Depth_stencil_format::NULL_DEPTH_STENCIL_FORMAT;

        ///
        ///
        ///
        GLuint depth_stencil_attachment_id = 0;

        //=================================================
        // Helper functions
        //=================================================

        void validate() const;

        void create_color_attachments(
            std::uint32_t w,
            std::uint32_t h,
            std::initializer_list<are::Color_attachment> color_attachments
        );

        void create_depth_stencil_attachments(
            std::uint32_t w,
            std::uint32_t h,
            Depth_stencil_format ds_format
        );

        static GLenum to_attachment_point(Depth_stencil_format format);

        static GLint to_internal_format(Depth_stencil_format format);

        /*
        static GLenum to_format(Depth_stencil_format format);

        static GLenum to_type(Depth_stencil_format format);
        */

    };

}

#endif //AGS_ARE_GL_FRAMEBUFFER_HPP
