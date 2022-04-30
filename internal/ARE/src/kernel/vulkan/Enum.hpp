//
// Created by avereniect on 3/12/22.
//

#ifndef AGS_ARE_VK10_ENUM_HPP
#define AGS_ARE_VK10_ENUM_HPP

#include "Includes.hpp"
#include "../Enums.hpp"

#include <ags/Types.hpp>

namespace ags::are::vk10 {

    vk::SampleCountFlagBits to_native_enum(Sample_count s);

    vk::Format to_native_enum(Channel_format, Primitive primitive);

    vk::Format to_native_enum(Stencil_format);

    vk::Format to_native_enum(Depth_format);

    vk::Format to_native_enum(Depth_stencil_format);

}

#endif //AGS_ARE_VK10_ENUM_HPP
