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

        uvec3r tri_normal = avml::normalize(avml::cross(v1 - v0, v2 - v0));

        real n_dot_d = dot(tri_normal, dir);
        auto tmp0 = avml::dot(tri_normal, v0);
        auto tmp1 = avml::dot(tri_normal, o);
        auto tmp2 = tmp0 - tmp1;
        real t = tmp2 / n_dot_d;
        vec3r p = o + t * dir;

        real area_abc = 0.5f * avml::length(avml::cross(v1 - v0, v2 - v0));
        real area_pbc = 0.5f * avml::length(avml::cross(v1 - p, v2 - p));
        real area_apc = 0.5f * avml::length(avml::cross(v0 - p, v2 - p));
        real area_abp = 0.5f * avml::length(avml::cross(v0 - p, v1 - p));

        real denominator = (1.00f / area_abc);

        real alpha = area_pbc * denominator;
        real beta = area_apc * denominator;
        real gamma = area_abp * denominator;

        const auto threshold = avel::bit_cast<float>(0x3f800000u + 1);

        if (alpha + beta + gamma > threshold) {
            ret.t = NAN;
            return ret;
        }

        ret.t = t;
        ret.location = p;
        ret.barycentric_coordinates = {alpha, beta, gamma};
        ret.normal = tri_normal;
        ret.front = n_dot_d >= 0.0;
        ret.object_id = -1;
        ret.triangle_id = -1;

        return ret;
    }

    AABB_intersection ray_aabb_intersection(vec3r o, uvec3r dir, AABB aabb) {
        using std::min;
        using std::max;

        real t = NAN;
        real tmin;
        real tmax;

        real tx1 = (aabb.min[0] - o[0]) / dir[0];
        real tx2 = (aabb.max[0] - o[0]) / dir[0];

        tmin = min(tx1, tx2);
        tmax = max(tx1, tx2);

        real ty1 = (aabb.min[1] - o[1]) / dir[1];
        real ty2 = (aabb.max[1] - o[1]) / dir[1];

        tmin = max(tmin, min(ty1, ty2));
        tmax = min(tmax, max(ty1, ty2));

        real tz1 = (aabb.min[2] - o[2]) / dir[2];
        real tz2 = (aabb.max[2] - o[2]) / dir[2];

        tmin = max(tmin, min(tz1, tz2));
        tmax = min(tmax, max(tz1, tz2));

        AABB_intersection ret{};
        if (tmax < tmin) {
            return ret;
        }

        t = tmin;

        ret.t = t;
        ret.location = o + t * dir;

        return ret;
    }

}
