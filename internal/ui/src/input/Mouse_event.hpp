//
// Created by avereniect on 1/21/22.
//

#ifndef AGS_MOUSE_EVENT_HPP
#define AGS_MOUSE_EVENT_HPP

#include "Input_event.hpp"

#include <cstdint>

namespace ags::ui {

    enum class Mouse_button : std::uint8_t {
        NULL_MOUSE_BUTTON,
        BUTTON1 = 1,
        BUTTON2,
        BUTTON3,
        BUTTON4,
        BUTTON5,
        BUTTON6,
        BUTTON7,
        BUTTON8,
        LEFT = 1,
        RIGHT = 2,
        MIDDLE = 3,
        LAST = BUTTON8
    };

    struct Mouse_motion_event {
        std::uint32_t x;
        std::uint32_t y;
    };

    struct Mouse_button_event {
        Button_action event;
        Mouse_button button;
    };

}

#endif //AGS_MOUSE_EVENT_HPP
