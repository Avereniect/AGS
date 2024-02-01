//
// Created by avereniect on 12/22/21.
//

#ifndef AGS_LBVH_HPP
#define AGS_LBVH_HPP

#include "Common.hpp"

#include <aul/Span.hpp>

#include <vector>

namespace ags::apt {

    struct BVH_AABB {
        vec3r min{-INFINITY};
        vec3r max{+INFINITY};

        int32 element_index = -1;
    };

    BVH_AABB intersection(BVH_AABB a, BVH_AABB b);

    BVH_AABB intersection(aul::Span<const BVH_AABB> aabbs);

    class LBVH8 {
    public:

        //=================================================
        // -ctors
        //=================================================

        explicit LBVH8(aul::Span<const BVH_AABB> aabbs);

        LBVH8() = default;
        LBVH8(const LBVH8&) = default;
        LBVH8(LBVH8&&) noexcept = delete; //TODO: Implement
        ~LBVH8() = default;

        //=================================================
        // Assignment operators
        //=================================================

        LBVH8& operator=(const LBVH8&) = default;
        LBVH8& operator=(LBVH8&&) noexcept = delete; //TODO: Implement

        //=================================================
        // Traversal
        //=================================================

        [[nodiscard]]
        std::uint32_t trace_ray(vec3r o, uvec3r dir) const;

    private:

        //=================================================
        // Instance members
        //=================================================

        std::vector<BVH_AABB> elements;

        //=================================================
        // Helper functions
        //=================================================

        ///
        /// \param aabbs
        /// \return
        static std::vector<BVH_AABB> build_heap(aul::Span<const BVH_AABB> aabbs);

    };

    class LBVH {
    public:

        //=================================================
        // -ctors
        //=================================================

        explicit LBVH(aul::Span<BVH_AABB> aabbs);

        LBVH() = default;
        LBVH(const LBVH&) = default;
        LBVH(LBVH&&) noexcept = delete; //TODO: Implement
        ~LBVH() = default;

        //=================================================
        // Assignment operators
        //=================================================

        LBVH& operator=(const LBVH&) = default;
        LBVH& operator=(LBVH&&) noexcept = delete; //TODO: Implement

        //=================================================
        // Traversal
        //=================================================

        [[nodiscard]]
        std::uint32_t trace_ray(vec3r o, uvec3r dir) const;

    private:

        //=================================================
        // Instance members
        //=================================================

        std::vector<BVH_AABB> elements{};

        //=================================================
        // Helper functions
        //=================================================

        ///
        /// \param aabbs
        /// \return
        static std::vector<BVH_AABB> build_heap(aul::Span<const BVH_AABB> aabbs);

    };

}

#endif //AGS_LBVH_HPP
