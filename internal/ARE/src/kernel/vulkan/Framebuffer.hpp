#ifndef AGS_ARE_VK_FRAMEBUFFER_HPP
#define AGS_ARE_VK_FRAMEBUFFER_HPP

#include <ags/Graphics_includes.hpp>

#include "Render_pass.hpp"
#include "../Framebuffer_common.hpp"

#include <cstdint>

#include <aul/containers/Array_map.hpp>


namespace ags::are::vk_kernel {

    class Shader_program;

    class Framebuffer {
    public:

        friend class Shader_program;

        //=================================================
        // -ctors
        //=================================================

        /*
        ///
        /// \param w Framebuffer width
        /// \param h Framebuffer height
        Framebuffer(std::uint32_t w, std::uint32_t h);
        */

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

        /*
        ///
        /// Specify the dimensions of the framebuffer.
        ///
        /// \param w Framebuffer width
        /// \param h Framebuffer height
        void resize(std::uint32_t w, std::uint32_t h);
        */

        ///
        /// Specify the attachments which this framebuffer should have. Any
        /// attachments which the framebuffer may already have are discarded
        ///
        /// \param w Framebuffer width
        /// \param h Framebuffer height
        /// \param color_attachments List of attachment descriptions
        /// \param samples Number of samples used for rendering
        void specify_attachments(
            std::uint32_t w, std::uint32_t h,
            std::initializer_list<are::Color_attachment> color_attachments,
            Sample_count samples = Sample_count::S1
        );

        ///
        ///
        ///
        void specify_attachments(
            std::uint32_t w, std::uint32_t h,
            std::initializer_list<are::Color_attachment> color_attachments,
            Depth_format depth_format,
            Sample_count samples = Sample_count::S1
        );

        void specify_attachments(
            std::uint32_t w, std::uint32_t h,
            std::initializer_list<Color_attachment> color_attachments,
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
            std::initializer_list<Color_attachment> color_attachments,
            Depth_stencil_format depth_stencil_format,
            Sample_count samples = Sample_count::S1
        );

        ///
        /// Releases the currently held resources.
        ///
        void clear();

        //=================================================
        // Accessors
        //=================================================

        [[nodiscard]]
        vk::Framebuffer native_handle() const;

        [[nodiscard]]
        vk::RenderPass native_renderpass() const;

        const std::vector<vk::ClearValue>& native_clear_values() const;


        ///
        /// \return Array containing width and height of framebuffer object
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

        //TODO: Replace with Vulkan implementation
        //[[nodiscard]]
        //aul::Span<const GLuint> native_color_attachment_handles() const;


        [[nodiscard]]
        Depth_format depth_attachment_format() const;

        [[nodiscard]]
        Stencil_format stencil_attachment_format() const;

        [[nodiscard]]
        Depth_stencil_format depth_stencil_attachment_format() const;

        //=================================================
        // Conversion operators
        //=================================================

        ///
        ///
        /// \return True if the current objects holds a resource. False otherwise
        [[nodiscard]]
        operator bool() const;

    private:

        //=================================================
        // Instance members
        //=================================================

        vk::Framebuffer handle;

        vk::RenderPass render_pass;

        std::array<std::uint32_t, 2> dims;

        Sample_count sample_count = Sample_count::S1;

        std::vector<vk::Image> attachment_images;

        std::vector<vk::ImageView> attachment_views;

        std::vector<Color_attachment> attachment_descriptions;

        std::vector<vk::AttachmentDescription> native_attachment_descs;

        //std::vector<vk::SubpassDescription> descriptors;
        //std::vector<vk::SubpassDependency> dependencies;

        std::vector<vk::AttachmentReference> attachment_refs;

        Depth_stencil_format depth_stencil_format = Depth_stencil_format::NULL_DEPTH_STENCIL_FORMAT;

        std::vector<vk::ClearValue> clear_values;

        //=================================================
        // Helper functions
        //=================================================

        vk::RenderPass create_render_pass(
            const std::initializer_list<Color_attachment>& attachments,
            Depth_stencil_format ds_format
        );

        vk::SubpassDescription create_subpass_description(
            const std::initializer_list<Color_attachment>& attachments,
            Depth_stencil_format ds_format
        );

        void create_attachments(
            const std::initializer_list<Color_attachment>& attachments,
            Depth_stencil_format ds_format
        );

        void create_attachment_references(
            const std::initializer_list<Color_attachment>& attachments,
            Depth_stencil_format ds_format
        );

        void create_attachment_views(
            const std::initializer_list<Color_attachment>& attachments,
            Depth_stencil_format ds_format
        );

        void create_native_attachment_descriptions(
            const std::initializer_list<Color_attachment>&,
            Depth_stencil_format ds_format
        );

        void create_clear_values(
            const std::initializer_list<Color_attachment>&,
            Depth_stencil_format ds_format
        );

    };

}

#endif //AGS_ARE_VK_FRAMEBUFFER_HPP
