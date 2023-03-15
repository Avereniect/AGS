//
// Created by avereniect on 3/12/22.
//

#ifndef AGS_ARE_VK_ENUM_HPP
#define AGS_ARE_VK_ENUM_HPP

#include <ags/Graphics_includes.hpp>

#include "../Enums_common.hpp"

#include <ags/Types.hpp>

namespace ags::are::vk_kernel {

    vk::SampleCountFlagBits to_native_enum(Sample_count s);

    vk::Format to_native_enum(Channel_format f, Primitive primitive);

    vk::Format to_native_enum(Stencil_format);

    vk::Format to_native_enum(Depth_format);

    vk::Format to_native_enum(Depth_stencil_format);

    vk::Format to_native_enum(Texture_format format);

    vk::Format to_native_enum(Attribute_type type);

}

#endif //AGS_ARE_VK_ENUM_HPP
