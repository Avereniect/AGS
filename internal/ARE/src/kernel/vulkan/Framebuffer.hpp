//
// Created by avereniect on 1/22/22.
//

#ifndef AGS_ARE_VK10_FRAMEBUFFER_HPP
#define AGS_ARE_VK10_FRAMEBUFFER_HPP

#include "Render_pass.hpp"

#include "Includes.hpp"

#include <aul/containers/Array_map.hpp>

#include <cstdint>

namespace ags::are::vk10 {

    struct Color_attachment {
        Sample_count sample_count = Sample_count::S1;
        Channel_format format = Channel_format::NULL_CHANNEL_FORMAT;
    };

    class Framebuffer {
    public:

        //=================================================
        // -ctors
        //=================================================

        ///
        /// \param w Framebuffer width
        /// \param h Framebuffer height
        Framebuffer(std::uint32_t w, std::uint32_t h);

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
        // Resource mutators
        //=================================================

        ///
        /// Specify the dimensions of the framebuffer.
        ///
        /// \param w Framebuffer width
        /// \param h Framebuffer height
        void resize(std::uint32_t w, std::uint32_t h);

        ///
        /// Specify the attachments which this framebuffer should have. Any
        /// attachments which the framebuffer may already have are discarded
        ///
        void specify_attachments(std::initializer_list<Color_attachment> color_attachments);

        ///
        ///
        void specify_attachments(std::initializer_list<Color_attachment>, Depth_format);

        void specify_attachments(std::initializer_list<Color_attachment>, Stencil_format);

        void specify_attachments(std::initializer_list<Color_attachment>, Depth_format, Stencil_format);

        ///
        /// Specify the attachments which this framebuffer should have. Any
        /// attachments which the framebuffer may already have are discarded and
        /// replaced.
        ///
        void specify_attachments(std::initializer_list<Color_attachment>, Depth_stencil_format);

        ///
        /// Releases the currently held resources
        ///
        void clear();

        //=================================================
        // Accessors
        //=================================================

        std::uint32_t width() const;

        std::uint32_t height() const;

        std::array<std::uint32_t, 2> dimensions() const;

        operator bool() const;

    private:

        //=================================================
        // Instance members
        //=================================================

        vk::Framebuffer handle;
        vk::RenderPass render_pass;

        std::array<std::uint32_t, 2> dims;

        std::vector<vk::ImageView> attachment_views;

        std::vector<vk::AttachmentDescription> attachments;
        std::vector<vk::SubpassDescription> descriptors;
        std::vector<vk::SubpassDependency> dependencies;
        std::vector<vk::AttachmentReference> attachment_refs;

        //=================================================
        // Helper functions
        //=================================================

        vk::Framebuffer create_handle(std::uint32_t w, std::uint32_t h);

    };

}

#endif //AGS_ARE_VK10_FRAMEBUFFER_HPP
