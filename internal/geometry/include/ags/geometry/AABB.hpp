//
// Created by avereniect on 3/10/22.
//

#ifndef AGS_AABB_HPP
#define AGS_AABB_HPP

#include <aul/Span.hpp>

namespace ags::geometry {

    template<class P, class D = void>
    class AABB {
    public:

        //=================================================
        // Static constants
        //=================================================

        static constexpr unsigned dimensionality = P::width;

        //=================================================
        // Type aliases
        //=================================================

        using real = typename P::scalar;

        using point = P;

        using data_type = D;

        //=================================================
        // -ctors
        //=================================================

        ///
        /// \param a
        /// \param b
        AABB(point a, point b, D d = {}):
            min_point(min(a, b)),
            max_point(max(a, b)),
            payload_data(d) {}

        AABB() = default;
        AABB(const AABB&) = default;
        AABB(AABB&&) noexcept = default;
        ~AABB() = default;

        //=================================================
        // Assignment operators
        //=================================================

        AABB& operator=(const AABB&)= default;
        AABB& operator=(AABB&&) noexcept = default;

        //=================================================
        // Accessors
        //=================================================

        point min_corner() const {
            return min_point;
        }

        point max_corner() const {
            return max_point;
        }

        D& payload() {
            return payload_data;
        }

        const D& payload() const {
            return payload_data;
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        point min_point{};
        point max_point{};

        D payload_data;

    };

    template<class P>
    class AABB<P, void>{
    public:

        //=================================================
        // Type aliases
        //=================================================

        using real = typename P::scalar;

        using point = P;

        //=================================================
        // -ctors
        //=================================================

        ///
        /// \param a
        /// \param b
        AABB(point a, point b):
            min_point(min(a, b)),
            max_point(max(a, b)) {}

        AABB() = default;
        AABB(const AABB&) = default;
        AABB(AABB&&) noexcept = default;
        ~AABB() = default;

        //=================================================
        // Assignment operators
        //=================================================

        AABB& operator=(const AABB&)= default;
        AABB& operator=(AABB&&) noexcept = default;

        //=================================================
        // Accessors
        //=================================================

        point min_corner() const {
            return min_point;
        }

        point max_corner() const {
            return max_point;
        }
    private:

        //=================================================
        // Instance members
        //=================================================

        point min_point{};
        point max_point{};

    };

    template<class P, class D>
    AABB<P, D> build_aabb(aul::Span<P> points, D&& data) {
        P max_corner{};
        P min_corner{};

        for (auto p : points) {
            max_corner = max(max_corner, p);
            min_corner = min(min_corner, p);
        }

        return AABB<P, D>{min_corner, max_corner, std::forward(data)};
    }

    ///
    /// \tparam P
    /// \tparam U
    /// \return
    template<class P, class D>
    AABB<P, D> bound_intersection(const AABB<P, D>& a, const AABB<P, D>& b, D&& data = {}) {
        return AABB<P, D>{
            min(a.min_corner(), b.min_corner()),
            max(b.max_corner(), b.max_corner()),
            std::forward(data)
        };
    }

    template<class P, class D>
    AABB<P, D> bound_union(const AABB<P, D>& a, const AABB<P, D>& b, D&& data = {}) {
        return AABB<P, D>{
            min(a.min_corner(), b.min_corner()),
            max(b.max_corner(), b.max_corner()),
            std::forward(data)
        };
    }

}

#endif //AGS_AABB_HPP
