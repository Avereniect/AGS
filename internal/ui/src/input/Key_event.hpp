//
// Created by avereniect on 1/21/22.
//

#ifndef AGS_KEY_EVENT_HPP
#define AGS_KEY_EVENT_HPP

#include "Input_event.hpp"

#include <cstdint>

namespace ags::ui {

    enum class Key : std::uint16_t {
        NULL_KEY,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z
    };

    struct Key_event {
        Key key;
        Button_action action;
    };

}

#endif //AGS_KEY_EVENT_HPP
