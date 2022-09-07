//
// Created by avereniect on 6/15/22.
//

#ifndef AGS_INSTERSECTION_TESTS_HPP
#define AGS_INSTERSECTION_TESTS_HPP

#include <gtest/gtest.h>

#include <Intersection.hpp>

namespace ags::apt::tests {

    TEST(Ray_triangle_intersection, Center) {
        vec3r o{0.25, 0.25, 1.0};
        uvec3r dir{0.0, 0.0, -1.0};

        Triangle triangle{};
        triangle.v0 = {0.0, 0.0, 0.0};
        triangle.v1 = {1.0, 0.0, 0.0};
        triangle.v2 = {0.0, 1.0, 0.0};

        auto inter = ray_triangle_intersection(o, dir, triangle);
        EXPECT_FLOAT_EQ(inter.t, 1.0);
    }

    TEST(Ray_AABB_intersection, Perpendicular) {
        vec3r o{0.0, 0.0, -2.0};
        uvec3r dir{0.0, 0.0, 1.0};

        AABB aabb{
            {-1.0, -1.0, -1.0},
            {+1.0, +1.0, +1.0}
        };

        auto inter = ray_aabb_intersection(o, dir, aabb);
        EXPECT_FLOAT_EQ(inter.t, 1.0);
    }

}

#endif //AGS_INSTERSECTION_TESTS_HPP
