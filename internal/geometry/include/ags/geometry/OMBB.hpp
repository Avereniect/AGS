//
// Created by avereniect on 9/4/22.
//

#ifndef AGS_GEOMETRY_OMBB_HPP
#define AGS_GEOMETRY_OMBB_HPP

#include <vector>

#include <aul/Span.hpp>

namespace ags::geometry {

    template<class M, class D>
    class OMBB {
        static_assert();
    public:

        //=================================================
        // Static constants
        //=================================================

        static constexpr unsigned dimensionality = M::width;

        //=================================================
        // Type aliases
        //=================================================

        using real = typename M::scalar;

        using point = typename M::vector;

        using matrix = M;

        using data_type = D;

        //=================================================
        // -ctors
        //=================================================

        OMBB(matrix orientation, point p0, point p1, D d = {});

        //=================================================
        // Assignment operators
        //=================================================

        OMBB& operator=(const OMBB&)= default;
        OMBB& operator=(OMBB&&) noexcept = default;

    private:

        //=================================================
        // Instance members
        //=================================================

        matrix orientation{1};

        point p0;

        point p1;

        D payload_data{};

    };

    namespace impl {

        template<std::uint32_t N, class P, class U>
        OMBB<P, U> build_omb(aul::Span<P> points, U&& u);

    }

    template<class P, class U>
    OMBB<P, U> build_omb(aul::Span<P> points, U&& u) {
        return impl::build_omb<P::width, P, U>(points, std::forward(u));
    }

}

#endif //AGS_GEOMETRY_OMBB_HPP
