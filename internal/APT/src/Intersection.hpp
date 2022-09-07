//
// Created by avereniect on 5/19/22.
//

#ifndef AGS_APT_INTERSECTION_HPP
#define AGS_APT_INTERSECTION_HPP

#include "Common.hpp"
#include "Shapes.hpp"

#include <cmath>

namespace ags::apt {

    struct Ray_triangle_intersection {

        //=================================================
        // Conversion operators
        //=================================================

        operator bool() const noexcept {
            return !std::isnan(t);
        }

        //=================================================
        // Instance members
        //=================================================

        float t;
        vec3r location;
        vec3r barycentric_coordinates;
        uvec3r normal;

        bool front;

        std::uint32_t object_id;
        std::uint32_t triangle_id;

    };

    ///
    /// \param o Ray origin
    /// \param dir Ray direction
    /// \param triangle Triangle to intersect ray with
    /// \return Intersection struct
    [[nodiscard]]
    Ray_triangle_intersection ray_triangle_intersection(vec3r o, uvec3r dir, Triangle triangle);




    struct AABB_intersection {

        //=================================================
        // Conversion operators
        //=================================================

        operator bool() const noexcept {
            return !std::isnan(t);
        }

        //=================================================
        // Instance members
        //=================================================

        float t;
        vec3r location;

    };

    ///
    /// \param o Ray origin
    /// \param dir Ray direction
    /// \param aabb AABB to intersect ray with
    /// \return Intersection struct
    AABB_intersection ray_aabb_intersection(vec3r o, uvec3r dir, AABB aabb);

}

#endif //AGS_APT_INTERSECTION_HPP
