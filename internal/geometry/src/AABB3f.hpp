//
// Created by avereniect on 3/10/22.
//

#ifndef AGS_AABB_HPP
#define AGS_AABB_HPP

#include <avml/AVML.hpp>

namespace ags::geometry {

    struct AABB3f {
        avml::vec3f min;
        avml::vec3f max;
    };

    AABB3f combine(AABB3f a, AABB3f b);

    AABB3f intersect(AABB3f a, AABB3f b);

}

#endif //AGS_AABB_HPP
