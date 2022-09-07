//
// Created by avereniect on 6/26/22.
//
#include "Texture_kernel.hpp"

namespace ags::are::vk_kernel {

    bool Texture_kernel::query_texture_support(Channel_format f, Primitive p) {
        vk::Format format = to_native_enum(f, p);

        auto& physical_device = Device_kernel::get_graphics_device().physical_device;
        vk::FormatProperties properties = physical_device.getFormatProperties(format);

        vk::FormatFeatureFlags flags = properties.optimalTilingFeatures;
        return bool(flags & vk::FormatFeatureFlagBits::eSampledImage);
    }

    std::pair<Channel_format, Primitive>
    Texture_kernel::suitable_texture_format(
        Channel_format f,
        Primitive p
    ) {

    }

}
