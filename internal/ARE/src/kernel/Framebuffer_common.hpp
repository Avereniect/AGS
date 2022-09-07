//
// Created by avereniect on 4/30/22.
//

#ifndef AGS_ARE_FRAMEBUFFER_HPP
#define AGS_ARE_FRAMEBUFFER_HPP

#include "Enums_common.hpp"

#include <ags/Types.hpp>

namespace ags::are {

    struct Color_attachment {
        Channel_format format = Channel_format::NULL_CHANNEL_FORMAT;
        ags::Primitive type = Primitive::NULL_PRIMITIVE;
    };

}

#endif //AGS_ARE_FRAMEBUFFER_HPP
