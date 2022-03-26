//
// Created by avereniect on 1/22/22.
//
#include "Framebuffer.hpp"
#include "Device_kernel.hpp"

#include <ags/Vulkan_core.hpp>

namespace ags::are::vk10 {

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
        specify_attachments(color_attachments, depth_attachment);
    }

    void Framebuffer::resize(std::uint32_t w, std::uint32_t h) {
        dims = {w, h};

        //TODO: Perform any Vulkan related work here
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

}