//
// Created by avereniect on 5/19/22.
//
#include "Intersection.hpp"

namespace ags::apt {

    Ray_triangle_intersection ray_triangle_intersection(vec3r o, uvec3r dir, Triangle triangle) {
        Ray_triangle_intersection ret{};

        auto& v0 = triangle.v0;
        auto& v1 = triangle.v1;
        auto& v2 = triangle.v2;

        v0 -= o;
        v1 -= o;
        v2 -= o;

        uvec3r tri_normal = avml::normalize(avml::cross(avml::normalize(v1 - v0), avml::normalize(v2 - v0)));

        real n_dot_d = dot(tri_normal, dir);
        real t = - (dot(tri_normal, o) + avml::dot(tri_normal, v0)) / n_dot_d;
        vec3r p = o - t * dir;

        real area_abc = 0.5 * avml::length(avml::cross(v1 - v0, v2 - v0));
        real area_pbc = 0.5 * avml::length(avml::cross(v1 - p, v2 - p));
        real area_apc = 0.5 * avml::length(avml::cross(v0 - p, v2 - p));
        real area_abp = 0.5 * avml::length(avml::cross(v0 - p, v1 - p));

        real denominator = (1.00f / area_abc);

        //TODO: Compute Barycentric coordinates
        real alpha = area_pbc * denominator;
        real beta = area_apc * denominator;
        real gamma = area_abp * denominator;

        const auto threshold = avel::bit_cast<float>(0x3f800000u + 1);

        if (alpha + beta + gamma > threshold) {
            ret.t = NAN;
        }

        ret.barycentric_coordinates = {alpha, beta, gamma};
        ret.normal = tri_normal;
        ret.front = n_dot_d >= 0.0;
        ret.object_id = -1;
        ret.triangle_id = -1;

        return ret;
    }

}
