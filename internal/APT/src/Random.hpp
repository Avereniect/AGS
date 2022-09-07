//
// Created by avereniect on 12/24/21.
//

#ifndef AGS_ARE_RANDOM_HPP
#define AGS_ARE_RANDOM_HPP

#include "Common.hpp"

#include <array>

namespace ags::apt {

    class Rand24 {
    public:

        //=================================================
        // -ctors
        //=================================================

        explicit Rand24(uint32 seed);

        Rand24() = default;
        Rand24(const Rand24&) = default;
        Rand24(Rand24&&) noexcept = default;
        ~Rand24() = default;

        //=================================================
        // Assignment Operators
        //=================================================

        Rand24& operator=(const Rand24&) = default;
        Rand24& operator=(Rand24&&) noexcept = default;

        //=================================================
        // Operators
        //=================================================

        uint32 get_int();

        float get_float();

    private:

        //=================================================
        // Constants
        //=================================================

        static constexpr uint32 a = 0x043F'D43FD;
        static constexpr uint32 c = 0x00C3'9EC3u;

        //=================================================
        // Instance members
        //=================================================

        uint32 x = 0;

    };

    ///
    /// \param seed
    /// \return Random 32-bit integer
    int32 uniform_random(int32 seed);

    ///
    /// \param seeds
    /// \return Vector of random 32-bit integers
    int32v uniform_random(int32v seeds);

    real uniform_random_n1_p1(int32 seed);
    realv uniform_random_n1_p1(int32v seeds);

    real uniform_random_npi_ppi(int32 seeds);
    realv uniform_random_npi_ppi(int32v seeds);

    std::array<real, 2> normal_random(int32 seeds);
    std::array<realv, 2> normal_random(int32v seeds);

    vec2r uniform_on_circle(int32 seed);
    vec2rv uniform_on_circle(int32v seeds);

    vec3r uniform_on_sphere(int32 seed);
    vec3rv uniform_on_sphere(int32v seeds);

    vec3r uniform_on_hemishere(int32 seed);
    vec3rv uniform_on_hemishere(int32v seeds);

}

#endif //AGS_ARE_RANDOM_HPP
