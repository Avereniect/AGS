//
// Created by avereniect on 6/14/22.
//

#ifndef AGS_APT_WINDOW_FUNCTIONS_HPP
#define AGS_APT_WINDOW_FUNCTIONS_HPP

#include "Common.hpp"

namespace ags::apt {

    real box_window(real x, real y);

    real pyramid_window(real x, real y);

    real cone_window(real x, real y);

    real han_window(real x, real y);

    real lanczos_window(real x, real y);

}

#endif //AGS_APT_WINDOW_FUNCTIONS_HPP
