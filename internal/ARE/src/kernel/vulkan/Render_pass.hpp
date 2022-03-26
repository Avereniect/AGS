//
// Created by avereniect on 1/22/22.
//

#ifndef AGS_ARE_VK10_RENDER_PASS_HPP
#define AGS_ARE_VK10_RENDER_PASS_HPP

#include "../Enums.hpp"

#include <vulkan/vulkan.hpp>

#include <cstdint>

namespace ags::are::vk10 {

    class Render_pass {
    public:

        //=================================================
        // -ctors
        //=================================================

        ///
        /// \param f Describes the render pass's channels
        /// \param s Number of samples per pixel in render pass
        Render_pass(Channel_format f, Sample_count s = Sample_count::S1);

        ///
        /// Creates a render pass with the channel format used by swap chains
        /// and 1 sample.
        ///
        Render_pass();
        Render_pass(Render_pass&) noexcept;
        Render_pass(const Render_pass&) = delete;
        ~Render_pass();

        //=================================================
        // Assignment operators
        //=================================================

        Render_pass& operator=(Render_pass&&) noexcept;
        Render_pass& operator=(const Render_pass&) = delete;

    private:

        //=================================================
        // Instance members
        //=================================================

        vk::RenderPass handle{};

        vk::AttachmentDescription attachment_desc;

        vk::SubpassDescription subpass_desc;

    };

}

#endif //AGS_ARE_VK10_RENDER_PASS_HPP
