//
// Created by avereniect on 3/12/22.
//

#ifndef AGS_ARE_VK10_ENUM_HPP
#define AGS_ARE_VK10_ENUM_HPP

#include <vulkan/vulkan.hpp>
#include "../Enums.hpp"

namespace ags::are::vk10 {

    vk::SampleCountFlagBits to_native_enum(Sample_count s);

}

#endif //AGS_ARE_VK10_ENUM_HPP
