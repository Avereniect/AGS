//
// Created by avereniect on 12/24/21.
//
#include "Random.hpp"

#include <limits>

namespace ags::apt {

    wholev uniform_random(wholev seeds) {
        wholev hash{0};

        const wholev byte_mask{static_cast<wholev>(0xFFFFFF00)};

        wholev byte0 = (seeds & byte_mask);
        wholev byte1 = ((seeds >> 0x08) & byte_mask);
        wholev byte2 = ((seeds >> 0x10) & byte_mask);
        wholev byte3 = ((seeds >> 0x18) & byte_mask);

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

    realv uniform_random_n1_p1(wholev seeds) {
        const real denom = 1.0f / std::numeric_limits<whole>::max();

        wholev t = uniform_random(seeds);
        return static_cast<realv>(t) * realv{denom};
    }

    realv uniform_random_npi_ppi(wholev seeds) {
        const real d = 3.14159265358979323 / std::numeric_limits<real>::max();
        return realv{uniform_random(seeds)} * realv{d};
    }

    std::array<realv, 2> normal_random_n1_p1(wholev seeds) {
        realv rand0 = uniform_random_n1_p1(seeds);
        realv rand1 = uniform_random_n1_p1(seeds + wholev{1289});

        realv t0 = sqrt(realv{-2.0f} * log(rand0));
        realv t1 = realv{6.2831853071795} * rand1;

        auto sc = sincos(t1);

        return {t0 * sc[0], t0 * sc[1]};
    }

    vec2rv uniform_on_circle(wholev seeds) {
        wholev hashes = uniform_random(seeds);
        realv angles = uniform_random_n1_p1(seeds);
        auto sc = sincos(angles);
        return {sc[1], sc[0]};
    }

    vec3rv uniform_on_sphere(wholev seeds) {
        realv angle = uniform_random_npi_ppi(seeds);
        realv z = uniform_random_n1_p1(seeds);

        realv t = sqrt(realv{1.0f} - z * z);

        auto sc = sincos(angle);

        realv x = t * sc[0];
        realv y = t * sc[1];

        return vec3rv{x, y, z};
    }

    vec3rv uniform_on_hemisphere(wholev seeds) {
        vec3rv tmp = uniform_on_sphere(seeds);
        tmp[2] = abs(tmp[2]);
        return tmp;
    }

}
