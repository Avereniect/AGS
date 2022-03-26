//
// Created by avereniect on 1/21/22.
//

#ifndef AGS_INPUT_EVENT_HPP
#define AGS_INPUT_EVENT_HPP

#include <cstdint>

namespace ags::ui {

    enum class Button_action : std::uint8_t{
        NULL_ACTION,
        PRESS,
        RELEASE
    };

}

#endif //AGS_INPUT_EVENT_HPP
