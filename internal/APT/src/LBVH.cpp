//
// Created by avereniect on 12/22/21.
//
#include "LBVH.hpp"
#include "Intersection.hpp"

#include <algorithm>
#include <queue>
#include <vector>

namespace ags::apt {

    //=========================================================================
    // class BVH_AABB
    //=========================================================================

    BVH_AABB intersection(BVH_AABB a, BVH_AABB b) {
        return {avml::min(a.min, b.min), avml::max(a.max, b.max), -1};
    }

    BVH_AABB intersection(aul::Span<const BVH_AABB> aabbs) {
        BVH_AABB ret{vec3r{+INFINITY}, vec3r{-INFINITY}, -1};

        for (const auto& e : aabbs) {
            ret = intersection(ret, e);
        }

        return ret;
    }

    //=========================================================================
    // Utilities
    //=========================================================================

    using partition_predicate = bool (*)(const BVH_AABB& l, const BVH_AABB& r);

    std::pair<std::vector<BVH_AABB>, std::vector<BVH_AABB>> partition_aabbs(std::vector<BVH_AABB> vec, partition_predicate p) {
        std::size_t size1 = vec.size() / 2;
        std::size_t size0 = vec.size() - size1;

        auto it0 = vec.begin();
        auto it1 = vec.begin() + size0;
        auto it2 = vec.end();
        std::nth_element(it0, it1, it2, p);

        std::vector<BVH_AABB> ret0{it0, it1};
        std::vector<BVH_AABB> ret1{it1, it2};

        return {ret0, ret1};
    }

    //=========================================================================
    // class LBVH8
    //=========================================================================

    LBVH8::LBVH8(aul::Span<const BVH_AABB> aabbs):
        elements(build_heap(aabbs)) {}

    std::uint32_t LBVH8::trace_ray(vec3r o, uvec3r dir) const {
        if (elements.empty()) {
            return -1;
        }

        std::queue<std::size_t> queue;
        queue.emplace(0);

        float closest_intersection = INFINITY;
        std::uint32_t ret = -1;

        while (!queue.empty()) {
            auto index = queue.front();

            if (elements.size() <= index) {
                queue.pop();
                continue;
            }

            auto aabb = elements[index];

            auto tmp = AABB{aabb.min, aabb.max};
            auto intersection = ray_aabb_intersection(o, dir, tmp);

            if (!intersection) {
                queue.pop();
                continue;
            }

            if (aabb.element_index != -1) {
                if (intersection.t < closest_intersection) {
                    closest_intersection = intersection.t;
                    ret = aabb.element_index;
                }
                queue.pop();
                continue;
            }

            queue.emplace(index * 8 + 1);
            queue.emplace(index * 8 + 2);
            queue.emplace(index * 8 + 3);
            queue.emplace(index * 8 + 4);

            queue.emplace(index * 8 + 5);
            queue.emplace(index * 8 + 6);
            queue.emplace(index * 8 + 7);
            queue.emplace(index * 8 + 8);

            queue.pop();
        }

        return ret;
    }

    std::vector<BVH_AABB> LBVH8::build_heap(aul::Span<const BVH_AABB> aabbs) {
        std::queue<std::tuple<std::size_t, std::vector<BVH_AABB>>> queue;
        queue.emplace(0, std::vector<BVH_AABB>{aabbs.begin(), aabbs.end()});

        static const auto x_predicate = [](const BVH_AABB& l, const BVH_AABB& r) {
            return (l.max[0] + l.min[0]) < (r.max[0] + r.min[0]);
        };

        static const auto y_predicate = [](const BVH_AABB& l, const BVH_AABB& r) {
            return (l.max[1] + l.min[1]) < (r.max[1] + r.min[1]);
        };

        static const auto z_predicate = [](const BVH_AABB& l, const BVH_AABB& r) {
            return (l.max[2] + l.min[2]) < (r.max[2] + r.min[2]);
        };

        std::vector<BVH_AABB> ret{};
        ret.reserve(aabbs.size());
        // Reserving by this amount is not optimal and can be improved

        while (!queue.empty()) {
            // Create partitions:
            auto [index, task] = queue.front();

            if (task.empty()) {
                queue.pop();
                continue;
            }

            if (task.size() == 1) {
                if (ret.size() < index + 1) {
                    ret.resize(index + 1);
                }
                ret[index] = task[0];
                queue.pop();
                continue;
            }

            BVH_AABB global_bvh = intersection({task.begin(), task.end()});

            if (ret.size() < index + 1) {
                ret.resize(index + 1);
            }
            ret[index] = global_bvh;

            //Add tasks to generate child nodes

            auto [x0, x1] = partition_aabbs(task, x_predicate);

            auto [xy00, xy01] = partition_aabbs(x0, y_predicate);
            auto [xy10, xy11] = partition_aabbs(x1, y_predicate);

            auto [xyz000, xyz001] = partition_aabbs(xy00, z_predicate);
            auto [xyz010, xyz011] = partition_aabbs(xy01, z_predicate);
            auto [xyz100, xyz101] = partition_aabbs(xy10, z_predicate);
            auto [xyz110, xyz111] = partition_aabbs(xy11, z_predicate);

            queue.emplace(index * 8 + 1, xyz000);
            queue.emplace(index * 8 + 2, xyz001);
            queue.emplace(index * 8 + 3, xyz010);
            queue.emplace(index * 8 + 4, xyz011);
            queue.emplace(index * 8 + 5, xyz100);
            queue.emplace(index * 8 + 6, xyz101);
            queue.emplace(index * 8 + 7, xyz110);
            queue.emplace(index * 8 + 8, xyz111);

            queue.pop();
        }

        return ret;
    }

    //=========================================================================
    // class LBVH2
    //=========================================================================

    /*
    LBVH::LBVH(aul::Span<BVH_AABB> aabbs):
        elements{build_heap(aabbs)} {}

    std::uint32_t LBVH::trace_ray(vec3r o, uvec3r dir) const {
        std::queue<std::size_t> aabb_queue{};
        aabb_queue.push(0);

        while (!aabb_queue.empty()) {
            std::size_t i = aabb_queue.front();
            aabb_queue.pop();

            AABB tmp{elements[i].min, elements[i].max};
            auto intersection = ray_aabb_intersection(o, dir, tmp);

            if (!intersection) {
                continue;
            }

            if (elements[i].element_index == -1) {
                aabb_queue.push(2 * i + 1);
                aabb_queue.push(2 * i + 2);
            } else {
                return elements[i].element_index;
            }
        }

        return -1;
    }
    */

    /*
    std::vector<BVH_AABB> LBVH::build_heap(aul::Span<const BVH_AABB> aabbs) {
        using predicate_type = bool (*)(const BVH_AABB& l, const BVH_AABB& r);

        static const auto x_predicate = [](const BVH_AABB& l, const BVH_AABB& r) {
            return (l.max[0] + l.min[0]) < (r.max[0] + r.min[0]);
        };

        static const auto y_predicate = [](const BVH_AABB& l, const BVH_AABB& r) {
            return (l.max[1] + l.min[1]) < (r.max[1] + r.min[1]);
        };

        static const auto z_predicate = [](const BVH_AABB& l, const BVH_AABB& r) {
            return (l.max[2] + l.min[2]) < (r.max[2] + r.min[2]);
        };

        std::queue<std::tuple<std::size_t, std::vector<AABB>>> work_queue;
        work_queue.emplace(0, std::vector{aabbs.begin(), aabbs.end()});

        std::vector<BVH_AABB> ret{aul::ceil2(aabbs.size() * 2 - 1)};
        // The above line will in the general case lead to more elements in the
        // vector than is strictly necessary

        while (!work_queue.empty()) {
            auto [i, items] = work_queue.front();

            if (items.empty()) {
                continue;
            }

            if (items.size() == 1) {
                ret[i] = items[0];
                continue;
            }

            //Construct global AABB
            vec3r global_max{-INFINITY};
            vec3r global_min{+INFINITY};

            for (const auto& aabb: aabbs) {
                global_max = avml::max(global_max, aabb.max);
                global_min = avml::min(global_min, aabb.min);
            }

            ret[i] = BVH_AABB{global_min, global_max, -1};

            real x_dim = global_max[0] - global_min[0];
            real y_dim = global_max[1] - global_min[1];
            real z_dim = global_max[2] - global_min[2];

            predicate_type predicate = nullptr;

            if (x_dim >= y_dim && x_dim >= z_dim) {
                predicate = x_predicate;
            } else if (y_dim >= x_dim && y_dim >= z_dim) {
                predicate = y_predicate;
            } else {
                predicate = z_predicate;
            }

            auto size0 = items.size() - (items.size() / 2);
            auto size1 = items.size() / 2;

            auto it0 = items.begin();
            auto it1 = it0 + size0;
            auto it2 = items.end();

            std::nth_element(it0, it1, it2, predicate);

            std::vector<AABB> items1{it0, it1};
            std::vector<AABB> items2{it1, it2};

            work_queue.emplace(2 * i + 1, std::move(items1));
            work_queue.emplace(2 * i + 2, std::move(items2));

            work_queue.pop();
        }

        return ret;
    }
    */

}