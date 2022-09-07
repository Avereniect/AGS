//
// Created by avereniect on 6/22/22.
//

#ifndef AGS_LBVH8_TESTS_HPP
#define AGS_LBVH8_TESTS_HPP

#include <gtest/gtest.h>

#include <LBVH.hpp>

namespace ags::apt {

    TEST(LBVH8, Single_element_test) {
        BVH_AABB aabb{
            {-1.0f, -1.0f, -1.0f},
            {+1.0f, +1.0f, +1.0f},
            48
        };

        vec3r o{0.0f, 0.0f, -2.0f};
        uvec3r dir{0.0f, 0.0f, 1.0f};

        aul::Span<BVH_AABB> span{&aabb, &aabb + 1};

        LBVH8 bvh{span};
        auto index = bvh.trace_ray(o, dir);
        EXPECT_EQ(index, 48);
    }

    TEST(LBVH8, Two_element_test) {
        BVH_AABB aabbs[] = {
            {
                {-1.0f, -1.0f, -1.0f},
                {+1.0f, +1.0f, +1.0f},
                48
            },
            {
                {-1.0f, -1.0f, +3.0f},
                {+1.0f, +1.0f, +4.0f},
                36
            }
        };

        aul::Span<BVH_AABB> span{aabbs};

        LBVH8 bvh{span};
        EXPECT_EQ(bvh.trace_ray({0.0f, 0.0f, -2.0f}, {0.0f, 0.0f,  1.0f}), 48);
        EXPECT_EQ(bvh.trace_ray({0.0f, 0.0f, 10.0f}, {0.0f, 0.0f, -1.0f}), 36);
    }

}

#endif //AGS_LBVH8_TESTS_HPP
