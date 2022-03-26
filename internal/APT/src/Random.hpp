//
// Created by avereniect on 12/24/21.
//

#ifndef AGS_RANDOM_HPP
#define AGS_RANDOM_HPP

#include "Common.hpp"

#include <array>

namespace ags::apt {

    wholev uniform_random(wholev seeds);

    realv uniform_random_n1_p1(wholev seeds);

    realv uniform_random_npi_ppi(wholev seeds);

    std::array<realv, 2> normal_random_n1_p1(wholev seeds);

    vec2rv uniform_on_circle(wholev seeds);

    vec3rv uniform_on_sphere(wholev seeds);

    vec3rv uniform_on_hemishere(wholev seeds);

}

#endif //AGS_RANDOM_HPP
