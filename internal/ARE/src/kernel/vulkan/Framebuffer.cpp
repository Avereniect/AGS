#include "Framebuffer.hpp"
#include "Framebuffer_kernel.hpp"
#include "Device_kernel.hpp"
#include "Texture_kernel.hpp"

#include "Enums.hpp"

namespace ags::are::vk_kernel {

    //=====================================================
    // -ctors
    //=====================================================

    /*
    Framebuffer::Framebuffer(Framebuffer&& other) noexcept:
        handle() {
        //TODO: Complete implementation
    }
    */

    Framebuffer::~Framebuffer() {
        Device_kernel::get_graphics_device().handle.destroy(render_pass);
        Device_kernel::get_graphics_device().handle.destroy(handle);

        //TODO: Destroy image views

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
        std::uint32_t w, std::uint32_t h,
        std::initializer_list<Color_attachment> color_attachments,
        Sample_count samples
    ) {
        specify_attachments(w, h, color_attachments, Depth_stencil_format::NULL_DEPTH_STENCIL_FORMAT, samples);
    }

    void Framebuffer::specify_attachments(
        std::uint32_t w, std::uint32_t h,
        std::initializer_list<Color_attachment> color_attachments,
        Depth_format depth_attachment,
        Sample_count samples
    ) {
        specify_attachments(w, h, color_attachments, to_depth_stencil_format(depth_attachment), samples);
    }

    void Framebuffer::specify_attachments(
        std::uint32_t w, std::uint32_t h,
        std::initializer_list<Color_attachment> color_attachments,
        Stencil_format stencil_attachment,
        Sample_count samples
    ) {
        specify_attachments(w, h, color_attachments, to_depth_stencil_format(stencil_attachment), samples);
    }

    void Framebuffer::specify_attachments(
        std::uint32_t w, std::uint32_t h,
        std::initializer_list<Color_attachment> color_attachments,
        Depth_format depth_attachment,
        Stencil_format stencil_attachment,
        Sample_count samples
    ) {
        specify_attachments(w, h, color_attachments, to_depth_stencil_format(depth_attachment, stencil_attachment), samples);
    }

    void Framebuffer::specify_attachments(
        std::uint32_t w, std::uint32_t h,
        std::initializer_list<Color_attachment> color_attachments,
        Depth_stencil_format ds_format,
        Sample_count samples
    ) {
        if (color_attachments.size() == 0 && ds_format == Depth_stencil_format::NULL_DEPTH_STENCIL_FORMAT) {
            AGS_WARN("Not framebuffer attachments were specified.");
            return ;
        }

        clear();

        dims = {w, h};

        sample_count = samples;

        depth_stencil_format = ds_format;

        attachment_descriptions = {color_attachments.begin(), color_attachments.end()};

        create_attachment_references(color_attachments, ds_format);
        create_native_attachment_descriptions(color_attachments, ds_format);
        create_attachments(color_attachments, ds_format);
        create_attachment_views(color_attachments, depth_stencil_format);
        create_clear_values(color_attachments, depth_stencil_format);

        render_pass = create_render_pass(color_attachments, depth_stencil_format);

        vk::FramebufferCreateInfo framebuffer_create_info{
            vk::FramebufferCreateFlagBits{},
            render_pass,
            attachment_views,
            dims[0], dims[1],
            1u //Number of layers for layered rendering.
        };

        handle = Device_kernel::get_graphics_device().handle.createFramebuffer(framebuffer_create_info);
    }

    /*
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
    */

    void Framebuffer::clear() {
        if (!handle) {
            return;
        }

        auto device = Device_kernel::get_graphics_device().handle;

        for (auto& image_view : attachment_views) {
            device.destroy(image_view);
        }
        attachment_views.clear();

        for (auto& image : attachment_images) {
            device.destroy(image);
        }
        attachment_images.clear();

        device.destroy(render_pass);
        render_pass = VK_NULL_HANDLE;

        device.destroy(handle);
        handle = VK_NULL_HANDLE;

        dims = {0, 0};
        sample_count = Sample_count::S1;
        depth_stencil_format = Depth_stencil_format::NULL_DEPTH_STENCIL_FORMAT;
    }

    //=====================================================
    // Accessors
    //=====================================================

    vk::Framebuffer Framebuffer::native_handle() const {
        return handle;
    }

    vk::RenderPass Framebuffer::native_renderpass() const {
        return render_pass;
    }

    const std::vector<vk::ClearValue>& Framebuffer::native_clear_values() const {
        return clear_values;
    }

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

    aul::Span<const are::Color_attachment> Framebuffer::color_attachments() const {
        return {attachment_descriptions.begin(), attachment_descriptions.end()};
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

    Framebuffer::operator bool() const {
        return handle;
    }

    //=====================================================
    // Helper functions
    //=====================================================

    vk::RenderPass Framebuffer::create_render_pass(
        const std::initializer_list<Color_attachment>& attachments,
        Depth_stencil_format ds_format
    ) {
        auto subpass = create_subpass_description(attachments, ds_format);

        vk::RenderPassCreateInfo info{
            vk::RenderPassCreateFlagBits{},
            native_attachment_descs,
            {1, &subpass},
            {0, nullptr}
        };

        auto ret = Device_kernel::get_graphics_device().handle.createRenderPass(info);
        return ret;
    }

    void Framebuffer::create_native_attachment_descriptions(
        const std::initializer_list<Color_attachment>& attachments,
        Depth_stencil_format ds_format
    ) {
        for (auto color_attachment : attachments) {
            native_attachment_descs.emplace_back(
                vk::AttachmentDescriptionFlags{},
                to_native_enum(color_attachment.format, color_attachment.type),
                to_native_enum(sample_count),
                vk::AttachmentLoadOp::eDontCare,
                vk::AttachmentStoreOp::eStore,
                vk::AttachmentLoadOp::eDontCare,
                vk::AttachmentStoreOp::eDontCare,
                vk::ImageLayout::eUndefined,
                vk::ImageLayout::ePresentSrcKHR
            );
        }

        if (ds_format != Depth_stencil_format::NULL_DEPTH_STENCIL_FORMAT) {
            native_attachment_descs.emplace_back(
                vk::AttachmentDescriptionFlags{},
                to_native_enum(ds_format),
                to_native_enum(sample_count),
                vk::AttachmentLoadOp::eDontCare,
                vk::AttachmentStoreOp::eStore,
                vk::AttachmentLoadOp::eDontCare,
                vk::AttachmentStoreOp::eDontCare,
                vk::ImageLayout::eUndefined,
                vk::ImageLayout::ePresentSrcKHR
            );
        }
    }

    vk::SubpassDescription Framebuffer::create_subpass_description(
        const std::initializer_list<Color_attachment>& attachments,
        Depth_stencil_format ds_format
    ) {
        vk::AttachmentReference* ds_attachment = nullptr;
        if (ds_format != Depth_stencil_format::NULL_DEPTH_STENCIL_FORMAT) {
            ds_attachment = &attachment_refs.back();
        }

        auto ret = vk::SubpassDescription{
            vk::SubpassDescriptionFlagBits{},
            vk::PipelineBindPoint::eGraphics,
            {0, nullptr},
            {std::uint32_t(attachments.size()), attachment_refs.data()},
            {0, nullptr},
            ds_attachment,
            {0, nullptr}
        };

        return ret;
    }

    void Framebuffer::create_attachment_views(
        const std::initializer_list<Color_attachment>& attachments,
        Depth_stencil_format ds_format
    ) {
        auto device = Device_kernel::get_graphics_device().handle;

        attachment_views.reserve(
            attachments.size() +
            std::uint32_t(ds_format != Depth_stencil_format::NULL_DEPTH_STENCIL_FORMAT)
        );

        auto it = attachment_images.begin();
        for (auto& attachment : attachments) {
            vk::ImageViewCreateInfo create_info{
                vk::ImageViewCreateFlagBits{},
                *it,
                vk::ImageViewType::e2D,
                to_native_enum(attachment.format, attachment.type),
                vk::ComponentMapping{},
                vk::ImageSubresourceRange{
                    vk::ImageAspectFlagBits::eColor,
                    0, //First mipmap layers
                    1, //Number of mipmap layers
                    0, //First array entry
                    1  //Number of array entries
                }
            };

            attachment_views.emplace_back(
                device.createImageView(create_info)
            );

            ++it;
        }

        if (ds_format == Depth_stencil_format::NULL_DEPTH_STENCIL_FORMAT) {
            return;
        }

        vk::ImageViewCreateInfo create_info{
            vk::ImageViewCreateFlagBits{},
            *it,
            vk::ImageViewType::e2D,
            to_native_enum(ds_format),
            vk::ComponentMapping{},
            vk::ImageSubresourceRange{
                vk::ImageAspectFlagBits::eDepth,
                0, //First mipmap layers
                1, //Number of mipmap layers
                0, //First array entry
                1  //Number of array entries
            }
        };

        attachment_views.emplace_back(device.createImageView(create_info));
    }

    void Framebuffer::create_attachments(
        const std::initializer_list<Color_attachment>& attachments,
        Depth_stencil_format ds_format
    ) {
        attachment_images.reserve(
            attachments.size() +
            std::uint32_t(ds_format != Depth_stencil_format::NULL_DEPTH_STENCIL_FORMAT)
        );

        for (auto& attachment : attachments) {
            vk::Extent3D extent{dims[0], dims[1], 1};

            auto native_format_enum = to_native_enum(attachment.format, attachment.type);

            vk::ImageFormatProperties format_properties{};

            vk::ImageCreateInfo create_info{
                vk::ImageCreateFlagBits{},
                vk::ImageType::e2D,
                native_format_enum,
                extent,
                1, //Number of mipmaps
                1, //Number of layers in array texture
                to_native_enum(sample_count),
                vk::ImageTiling::eOptimal,
                vk::ImageUsageFlagBits::eColorAttachment,
                vk::SharingMode::eExclusive, //Replace once multithreading is introduced
                {1, &Device_kernel::get_graphics_device().graphics_queue_index},
                vk::ImageLayout::eUndefined
            };

            attachment_images.emplace_back(
                Device_kernel::get_graphics_device().handle.createImage(create_info)
            );

            Framebuffer_kernel::allocate_image_memory(attachment_images.back(), Buffer_usage{});
        }

        if (ds_format == Depth_stencil_format::NULL_DEPTH_STENCIL_FORMAT) {
            return;
        }

        auto native_depth_format_enum = to_native_enum(ds_format);

        vk::ImageCreateInfo create_info{
            vk::ImageCreateFlagBits{},
            vk::ImageType::e2D,
            native_depth_format_enum,
            vk::Extent3D(dims[0], dims[1], 1),
            1, //Number of mipmaps
            1, //Number of layers in array texture
            to_native_enum(sample_count),
            vk::ImageTiling::eOptimal,
            vk::ImageUsageFlagBits::eDepthStencilAttachment,
            vk::SharingMode::eExclusive, //Replace once multithreading is introduced
            {1, &Device_kernel::get_graphics_device().graphics_queue_index},
            vk::ImageLayout::eUndefined
        };

        //TODO: Allocate image memory
        //TODO: Use memory kernel facilities once implemented

        attachment_images.emplace_back(
            Device_kernel::get_graphics_device().handle.createImage(create_info)
        );

        Framebuffer_kernel::allocate_image_memory(attachment_images.back(), Buffer_usage{});
    }

    void Framebuffer::create_attachment_references(
        const std::initializer_list<Color_attachment>& attachments,
        ags::are::Depth_stencil_format ds_format
    ) {
        attachment_refs.reserve(
            attachments.size() +
            std::uint32_t(ds_format != Depth_stencil_format::NULL_DEPTH_STENCIL_FORMAT)
        );

        std::uint32_t i = 0;

        for (; i < attachments.size(); ++i) {
            attachment_refs.emplace_back(
                i,
                vk::ImageLayout::eColorAttachmentOptimal
            );
        }

        if (ds_format == Depth_stencil_format::NULL_DEPTH_STENCIL_FORMAT) {
            return;
        }

        vk::ImageLayout layout{};
        switch (ds_format) {
        case Depth_stencil_format::STENCIL8:
            layout = vk::ImageLayout::eDepthStencilAttachmentOptimal;
            break;
        case Depth_stencil_format::INT24:
        case Depth_stencil_format::FLOAT32:
            layout = vk::ImageLayout::eDepthStencilAttachmentOptimal;
            break;
        case Depth_stencil_format::INT24_STENCIL8:
        case Depth_stencil_format::FLOAT32_STENCIL8:
            layout = vk::ImageLayout::eDepthStencilAttachmentOptimal;
            break;
        }

        attachment_refs.emplace_back(i, layout);
    }

    void Framebuffer::create_clear_values(
        const std::initializer_list<Color_attachment>& color_attachments,
        Depth_stencil_format ds_format
    ) {
        clear_values.reserve(color_attachments.size() + 1);

        vk::ClearValue clear{};
        clear.color = vk::ClearColorValue(1.0f, 1.0f, 1.0f, 1.0f);
        clear.depthStencil = vk::ClearDepthStencilValue{0.0f, 0x00};

        for (auto& color_attachment : color_attachments) {
            clear_values.emplace_back(clear);
        }

        if (ds_format != Depth_stencil_format::NULL_DEPTH_STENCIL_FORMAT) {
            clear_values.emplace_back(clear);
        }
    }

}