//
// Created by avereniect on 1/22/22.
//
#include "Framebuffer.hpp"
#include "Device_kernel.hpp"

#include "Enums.hpp"

namespace ags::are::vk_kernel {

    //=====================================================
    // -ctors
    //=====================================================

    Framebuffer::Framebuffer(std::uint32_t w, std::uint32_t h):
        handle(create_handle(w, h)),
        render_pass(VK_NULL_HANDLE),
        dims({w, h}),
        attachment_views(),
        descriptors(),
        dependencies(),
        attachment_refs() {}

    Framebuffer::Framebuffer(Framebuffer&& other) noexcept:
        handle() {
        //TODO: Complete implementation
    }

    Framebuffer::~Framebuffer() {
        Device_kernel::get_graphics_device().handle.destroy(handle);

        //Destroy other acquired resources
    }

    //=====================================================
    // Assignment operators
    //=====================================================

    //Framebuffer& Framebuffer::operator=(Framebuffer&& rhs) noexcept;

    //=====================================================
    // Resource mutators
    //=====================================================

    void Framebuffer::specify_attachments(
        std::initializer_list<Color_attachment> color_attachments
    ) {
        specify_attachments(color_attachments, Depth_stencil_format::NULL_DEPTH_STENCIL_FORMAT);
    }

    void Framebuffer::specify_attachments(
        std::initializer_list<Color_attachment> color_attachments,
        Depth_format depth_attachment
    ) {
        specify_attachments(color_attachments, to_depth_stencil_format(depth_attachment));
    }

    void Framebuffer::specify_attachments(
        std::initializer_list<Color_attachment> color_attachments,
        Stencil_format stencil_attachment
    ) {
        specify_attachments(color_attachments, to_depth_stencil_format(stencil_attachment));
    }

    void Framebuffer::specify_attachments(
        std::initializer_list<Color_attachment> color_attachments,
        Depth_format depth_attachment,
        Stencil_format stencil_attachment
    ) {
        specify_attachments(color_attachments, to_depth_stencil_format(depth_attachment, stencil_attachment));
    }

    void Framebuffer::specify_attachments(
        std::initializer_list<Color_attachment> color_attachments,
        Depth_stencil_format depth_stencil_format
    ) {
        Depth_format depth_format = to_depth_format(depth_stencil_format);
        Stencil_format stencil_format = to_stencil_format(depth_stencil_format);

        //TODO: Issue warning if no attachments were specified
        for (auto it = color_attachments.begin(); it != color_attachments.end(); ++it) {
            attachment_descs.emplace_back(
                vk::AttachmentDescriptionFlags{},
                to_native_enum(it->format, it->type),
                to_native_enum(it->sample_count),
                vk::AttachmentLoadOp::eLoad,
                vk::AttachmentStoreOp::eStore,
                vk::AttachmentLoadOp::eLoad,
                vk::AttachmentStoreOp::eStore,
                vk::ImageLayout::eUndefined,
                vk::ImageLayout::ePresentSrcKHR
            );
        }

        if (is_combined_format(depth_stencil_format)) {
            attachment_descs.emplace_back(
                vk::AttachmentDescriptionFlags{},
                to_native_enum(depth_stencil_format),
                to_native_enum(Sample_count::S1),
                vk::AttachmentLoadOp::eLoad,
                vk::AttachmentStoreOp::eStore,
                vk::AttachmentLoadOp::eLoad,
                vk::AttachmentStoreOp::eStore,
                vk::ImageLayout::eUndefined,
                vk::ImageLayout::ePresentSrcKHR
            );
        } else {
            if (depth_format != Depth_format::NULL_DEPTH_FORMAT) {
                attachment_descs.emplace_back(
                    vk::AttachmentDescriptionFlags{},
                    to_native_enum(depth_format),
                    to_native_enum(Sample_count::S1),
                    vk::AttachmentLoadOp::eLoad,
                    vk::AttachmentStoreOp::eStore,
                    vk::AttachmentLoadOp::eLoad,
                    vk::AttachmentStoreOp::eStore,
                    vk::ImageLayout::eUndefined,
                    vk::ImageLayout::ePresentSrcKHR
                );
            }

            if (stencil_format != Stencil_format::NULL_STENCIL_FORMAT) {
                attachment_descs.emplace_back(
                    vk::AttachmentDescriptionFlags{},
                    to_native_enum(stencil_format),
                    to_native_enum(Sample_count::S1),
                    vk::AttachmentLoadOp::eLoad,
                    vk::AttachmentStoreOp::eStore,
                    vk::AttachmentLoadOp::eLoad,
                    vk::AttachmentStoreOp::eStore,
                    vk::ImageLayout::eUndefined,
                    vk::ImageLayout::ePresentSrcKHR
                );
            }
        }

        //Create attachment references

        attachment_refs.resize(attachment_descs.size());
        std::uint32_t i = 0;
        for (; i < color_attachments.size(); ++i) {
            attachment_refs.emplace_back(
                i,
                vk::ImageLayout::eColorAttachmentOptimal
            );
        }

        if (is_combined_format(depth_stencil_format)) {
            attachment_refs.emplace_back(
                i,
                vk::ImageLayout::eDepthStencilAttachmentOptimal
            );
            ++i;
        } else {
            //TODO: Specify that VK_KHR_maintenance2 extensions is required
            //Note: Switch to non-KHR versions of enums if upgrading program to Vulkan 1.2
            if (depth_format != Depth_format::NULL_DEPTH_FORMAT) {
                attachment_refs.emplace_back(
                    i,
                    vk::ImageLayout::eDepthAttachmentOptimalKHR
                );
                ++i;
            }

            if (stencil_format != Stencil_format::NULL_STENCIL_FORMAT) {
                attachment_refs.emplace_back(
                    i,
                    vk::ImageLayout::eStencilAttachmentOptimalKHR
                );
                ++i;
            }
        }

        //TODO: Handle attachment descriptions for depth, stencil, and depth-stencil

        //TODO: Specify subpasses
        vk::SubpassDescription subpass_description{
            vk::SubpassDescriptionFlagBits{},
            vk::PipelineBindPoint::eGraphics,
            0u, //TODO: Proper handling of input attachments
            nullptr,
            static_cast<std::uint32_t>(color_attachments.size()),
            attachment_refs.data(),
            nullptr,
            attachment_refs.data() + color_attachments.size(),
            0, //TODO: Proper handling of reserve attachments
            nullptr
        };

        vk::RenderPassCreateInfo render_pass_create_info{
            vk::RenderPassCreateFlagBits{},
            static_cast<std::uint32_t>(attachment_descs.size()),
            attachment_descs.data(),
            1, //TODO: Handle variable subpasses
            &subpass_description,
            0, //TODO: Handle dependencies between different subpasses
            nullptr
        };

        render_pass = Device_kernel::get_graphics_device().handle.createRenderPass(render_pass_create_info);

        //TODO: Move creation of framebuffer elsewhere?
        vk::FramebufferCreateInfo framebuffer_create_info{
            vk::FramebufferCreateFlagBits{},
            render_pass,
            static_cast<std::uint32_t>(attachment_descs.size()),
            attachment_views.data(),
            dims[0],
            dims[1],
            1u //TODO: Specify correct number of layers
        };

        handle = Device_kernel::get_graphics_device().handle.createFramebuffer(framebuffer_create_info);
    }

    void Framebuffer::resize(std::uint32_t w, std::uint32_t h) {
        dims = {w, h};

        //TODO: Perform Vulkan work
        // Framebuffer will need to be recreated

        vk::FramebufferCreateInfo framebuffer_create_info{
            vk::FramebufferCreateFlagBits{},
            render_pass,
            static_cast<std::uint32_t>(attachment_descriptions.size()),
            attachment_views.data(),
            dims[0],
            dims[1],
            1u //TODO: Specify correct number of layers
        };
    }

    //=====================================================
    // Helper functions
    //=====================================================

    vk::Framebuffer Framebuffer::create_handle(std::uint32_t w, std::uint32_t h) {
        vk::AttachmentDescription color_attachment{
            vk::AttachmentDescriptionFlags{},
            Kernel_base::get_presentation_format(),
            vk::SampleCountFlagBits::e1,
            vk::AttachmentLoadOp::eClear,
            vk::AttachmentStoreOp::eStore,
            vk::AttachmentLoadOp::eDontCare,
            vk::AttachmentStoreOp::eDontCare,
            vk::ImageLayout::eUndefined,
            vk::ImageLayout::ePresentSrcKHR
        };

        vk::AttachmentReference attachment_ref{
            0,
            vk::ImageLayout::eColorAttachmentOptimal
        };

        vk::SubpassDescription subpass_desc{
            vk::SubpassDescriptionFlags{},
            vk::PipelineBindPoint::eGraphics,
            0,
            nullptr,
            1,
            &attachment_ref,
            nullptr,
            nullptr,
            0,
            nullptr
        };

        vk::RenderPassCreateInfo render_pass_create_info{
            vk::RenderPassCreateFlags{},
            attachments,
            descriptors,
            dependencies
        };

        render_pass = Device_kernel::get_graphics_device().handle.createRenderPass(render_pass_create_info);

        //TODO: Fill attachment views

        vk::FramebufferCreateInfo create_info {
            vk::FramebufferCreateFlagBits{},
            render_pass,
            attachment_views,
            w,
            h,
            1
        };

        return Device_kernel::get_graphics_device().handle.createFramebuffer(create_info);
    }

    //=====================================================
    // Accessors
    //=====================================================

    std::uint32_t Framebuffer::width() const {
        return dims[0];
    }

    std::uint32_t Framebuffer::height() const {
        return dims[1];
    }

    std::array<std::uint32_t, 2> Framebuffer::dimensions() const {
        return dims;
    }

    Framebuffer::operator bool() const {
        return handle;
    }

}