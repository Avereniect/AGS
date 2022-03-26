//
// Created by avereniect on 1/19/22.
//
#include "Optics.hpp"
#include <cmath>

namespace ags::apt {

    float critical_angle(float n0, float n1) {
        return std::asin(n0 / n1);
    }

}
