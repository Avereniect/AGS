//
// Created by avereniect on 12/24/21.
//
#include "Random.hpp"

#include <limits>

namespace ags::apt {

    int32 uniform_random(int32 seed) {
        int32 hash = 0;

        seed += 0xDEADBEEF;

        const auto byte_mask = static_cast<int32>(0xFFFFFF00);

        int32 byte0 = (seed & byte_mask);
        int32 byte1 = ((seed >> 0x08) & byte_mask);
        int32 byte2 = ((seed >> 0x10) & byte_mask);
        int32 byte3 = ((seed >> 0x18) & byte_mask);

        hash += byte0;
        hash += (hash << 10);
        hash ^= (hash >> 6);

        hash += byte1;
        hash += (hash << 10);
        hash ^= (hash >> 6);

        hash += byte2;
        hash += (hash << 10);
        hash ^= (hash >> 6);

        hash += byte3;
        hash += (hash << 10);
        hash ^= (hash >> 6);

        hash += (hash << 3);
        hash ^= (hash >> 11);
        hash += (hash << 15);

        return hash;
    }

    int32v uniform_random(int32v seeds) {
        int32v hash{0};

        seeds += int32v{static_cast<int32>(0xDEADBEEF)};

        const auto byte_mask = static_cast<int32v>(0xFFFFFF00);

        int32v byte0 = (seeds & byte_mask);
        int32v byte1 = ((seeds >> 0x08) & byte_mask);
        int32v byte2 = ((seeds >> 0x10) & byte_mask);
        int32v byte3 = ((seeds >> 0x18) & byte_mask);

        hash += byte0;
        hash += (hash << 10);
        hash ^= (hash >> 7);

        hash += byte1;
        hash += (hash << 10);
        hash ^= (hash >> 6);

        hash += byte2;
        hash += (hash << 10);
        hash ^= (hash >> 5);

        hash += byte3;
        hash += (hash << 10);
        hash ^= (hash >> 4);

        hash += (hash << 3);
        hash ^= (hash >> 11);
        hash += (hash << 15);

        return hash;
    }

    real uniform_random_n1_p1(int32 seed) {
        const real denom = 1.0f / real(std::numeric_limits<int32>::max());

        int32 t = uniform_random(seed);
        return static_cast<real>(t) * real{denom};
    }

    realv uniform_random_n1_p1(int32v seeds) {
        const real denom = 1.0 / real(std::numeric_limits<int32v::scalar_type>::max());

        int32v t = uniform_random(seeds);
        return static_cast<realv>(t) * realv{denom};
    }

    real uniform_random_npi_ppi(int32 seed) {
        const real d = 3.14159265358979323 / std::numeric_limits<real>::max();
        return real(uniform_random(seed)) * real{d};
    }

    realv uniform_random_npi_ppi(int32v seeds) {
        const real d = 3.14159265358979323 / std::numeric_limits<real>::max();
        return realv{uniform_random(seeds)} * realv{d};
    }

    std::array<real, 2> normal_random(int32 seed) {
        using std::sqrt;
        using std::log;

        //TODO: Handle case where this is 0
        //TODO: Replace with generation of random number in [0.0, 1.0 range]
        real rand0 = uniform_random_n1_p1(seed);
        real rand1 = uniform_random_n1_p1(seed * (seed + 16));

        real t0 = sqrt(real{-2.0} * log(rand0 * 0.5 + 0.5));
        real t1 = real{6.2831853071795} * rand1 * 0.5 + 0.5;

        //TODO: Replace with singular call to
        auto s = std::sin(t1);
        auto c = std::cos(t1);

        return {t0 * s, t0 * c};

        /*
        auto sc = sincos(t1);
        return {t0 * sc[0], t0 * sc[1]};
        */
    }

    std::array<realv, 2> normal_random(int32v seeds) {
        realv rand0 = uniform_random_n1_p1(seeds);
        realv rand1 = uniform_random_n1_p1(seeds + int32v{1289});

        realv t0 = sqrt(realv{-2.0f} * log(rand0));
        realv t1 = realv{6.2831853071795} * rand1;

        auto sc = sincos(t1);

        return {t0 * sc[0], t0 * sc[1]};
    }

    vec2rv uniform_on_circle(int32v seeds) {
        int32v hashes = uniform_random(seeds);
        realv angles = uniform_random_n1_p1(seeds);
        auto sc = sincos(angles);
        return {sc[1], sc[0]};
    }

    vec3r uniform_on_sphere(int32 seeds) {
        using std::sqrt;

        real angle = uniform_random_npi_ppi(seeds);
        real z = uniform_random_n1_p1(seeds);

        real t = sqrt(real{1.0f} - z * z);

        auto s = std::sin(angle);
        auto c = std::cos(angle);

        //TODO: Use explicit call to sincos
        //auto sc = sincos(angle);

        real x = t * s;
        real y = t * c;

        return vec3r{x, y, z};
    }

    vec3rv uniform_on_sphere(int32v seeds) {
        realv angle = uniform_random_npi_ppi(seeds);
        realv z = uniform_random_n1_p1(seeds);

        realv t = sqrt(realv{1.0f} - z * z);

        auto sc = sincos(angle);

        realv x = t * sc[0];
        realv y = t * sc[1];

        return vec3rv{x, y, z};
    }

    vec3r uniform_on_hemisphere(int32 seeds) {
        vec3r tmp = uniform_on_sphere(seeds);
        tmp[2] = abs(tmp[2]);
        return tmp;
    }

    vec3rv uniform_on_hemisphere(int32v seeds) {
        vec3rv tmp = uniform_on_sphere(seeds);
        tmp[2] = abs(tmp[2]);
        return tmp;
    }

}
