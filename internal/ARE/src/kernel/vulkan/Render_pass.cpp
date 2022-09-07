//
// Created by avereniect on 1/22/22.
//
#include "Render_pass.hpp"

#include <ags/Vulkan_core.hpp>

namespace ags::are::vk_kernel {

    //=====================================================
    // -ctors
    //=====================================================

    Render_pass::Render_pass() {
        attachment_desc.flags = vk::AttachmentDescriptionFlags{};

        //This is assumed to be the format which is used by the swap chain images
        attachment_desc.format = vk::Format::eR8G8B8A8Srgb;
        attachment_desc.samples = vk::SampleCountFlagBits::e1;
        attachment_desc.loadOp = vk::AttachmentLoadOp::eClear;
        attachment_desc.storeOp = vk::AttachmentStoreOp::eStore;
        attachment_desc.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
        attachment_desc.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
        attachment_desc.initialLayout = vk::ImageLayout::eUndefined;
        attachment_desc.finalLayout = vk::ImageLayout::ePresentSrcKHR;

        subpass_desc.flags = vk::SubpassDescriptionFlagBits{};
        subpass_desc.
    }

}
