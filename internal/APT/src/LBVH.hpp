//
// Created by avereniect on 12/22/21.
//

#ifndef AGS_LBVH_HPP
#define AGS_LBVH_HPP

#include "Common.hpp"

namespace ags::apt {

    struct AABB {
        vec3r min{-INFINITY};
        vec3r max{+INFINITY};

        whole element_index = -1;
    };

    struct LBVH {

        LBVH();
        ~LBVH();

        std::vector<AABB> elements;

    };

}

#endif //AGS_LBVH_HPP
