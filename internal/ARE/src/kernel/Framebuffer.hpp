//
// Created by avereniect on 4/30/22.
//

#ifndef AGS_ARE_FRAMEBUFFER_HPP
#define AGS_ARE_FRAMEBUFFER_HPP

#include "Enums.hpp"

#include <ags/Types.hpp>

namespace ags::are {

    struct Color_attachment {
        Sample_count sample_count = Sample_count::S1;
        Channel_format format = Channel_format::NULL_CHANNEL_FORMAT;
        ags::Primitive type = Primitive::NULL_PRIMITIVE;
    };

}

#endif //AGS_ARE_FRAMEBUFFER_HPP
