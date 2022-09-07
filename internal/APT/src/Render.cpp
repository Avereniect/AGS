//
// Created by avereniect on 12/22/21.
//

#include "Common.hpp"
#include "Render.hpp"

#include "Window_functions.hpp"
#include "Intersection.hpp"
#include "Random.hpp"

#include <iostream>

#include <aul/Math.hpp>
#include <aul/containers/Matrix.hpp>

#include <thread>

#include <aul/containers/Matrix.hpp>

namespace ags::apt {

    color evaluate_world(uvec3r dir) {
        const uvec3r peak = avml::assume_normalized({0.0, 1.0, 0.0});

        const color black{0.0, 0.0, 0.0};
        return color{0.25, 0.50, 0.75} * avml::dot(dir, peak);
    }

    color trace_path(const Scene& scene, vec3r origin, uvec3r dir) {
        //TODO: Trace scene instead of this single triangle

        Triangle triangle{};
        triangle.v0 = { 0.0, 1.0,  0.5};
        triangle.v1 = {-0.5, 1.0, -0.5};
        triangle.v2 = { 0.5, 1.0, -0.5};

        auto intersection = ray_triangle_intersection(origin, dir, triangle);
        if (intersection) {
            return {1.0, 1.0, 1.0};
        } else {
            return evaluate_world(dir);
        }
    }

    void thread_worker(
        const Render_settings& settings,
        const Scene& scene,
        Image* img,
        aul::Matrix<Rand24, 2>* generators,
        std::uint32_t thread_index
    ) {
        //Compute range of pixels that need to be computed
        Image& image = *img;
        auto& gens = *generators;

        const auto image_pixel_count = settings.image_width * settings.image_height;
        const auto thread_pixel_count = aul::divide_ceil(image_pixel_count, settings.thread_count);

        uvec3r camera_z = -scene.camera.forward;
        uvec3r camera_y = scene.camera.up;
        uvec3r camera_x = avml::normalize(avml::cross(camera_y, camera_z));

        real sensor_width  = 0.0f;
        real sensor_height = 0.0f;

        if (image.width() < image.height()) {
            sensor_height = scene.camera.sensor_size;
            sensor_width  = scene.camera.sensor_size * float(image.width()) / float(image.height());
        } else {
            sensor_height = scene.camera.sensor_size * float(image.height()) / float(image.width());
            sensor_width  = scene.camera.sensor_size;
        }

        uint32 i = 0;
        for (uint32 y = 0; y < image.height(); ++y) {
            for (uint32 x = 0; x < image.width(); ++x, ++i)  {
                i %= settings.thread_count;

                if (i % settings.thread_count != thread_index) {
                    continue;
                }

                const auto x_numer = +static_cast<int32>((x - image.width())  + x + 1);
                const auto y_numer = -static_cast<int32>((y - image.height()) + y + 1);

                color c = {0.0, 0.0, 0.0};
                for (uint32 s = 0; s < settings.samples_per_pixel; ++s) {
                    real sample_offset_x = 2.0f * gens[y][x].get_float() - 1.0f;
                    real sample_offset_y = 2.0f * gens[y][x].get_float() - 1.0f;

                    //real sample_offset_x = settings.pixel_filter_width * rand0;
                    //real sample_offset_y = settings.pixel_filter_width * rand1;

                    const real x_ndc = (x_numer + sample_offset_x) / real(image. width()) + scene.camera.offset[0];
                    const real y_ndc = (y_numer + sample_offset_y) / real(image.height()) + scene.camera.offset[1];

                    //Sensor size might be off by a factor of 2
                    const uvec3r dir = avml::normalize(
                          camera_x * x_ndc * sensor_width
                        + camera_y * y_ndc * sensor_height
                        - camera_z * scene.camera.focal_length
                    );

                    c += trace_path(scene, scene.camera.location, dir);
                }

                image[x][y] = Image::pixel_type{c[0], c[1], c[2]};
            }
        }
    }

    Image threaded_render(const Render_settings& settings, const Scene& scene) {
        std::uint32_t thread_count = (settings.thread_count == 0) ? std::thread::hardware_concurrency() : settings.thread_count;

        Rand24 seed_generator{};
        Image image{settings.image_width, settings.image_height};
        aul::Matrix<Rand24, 2> generators{{image.width(), image.height()}};
        for (uint32 y = 0; y < image.height(); ++y) {
            for (uint32 x = 0; x < image.width(); ++x) {
                generators[y][x] = Rand24{seed_generator.get_int()};
            }
        }

        std::vector<std::thread> threads;
        for (std::uint32_t i = 0; i < thread_count; ++i) {
            threads.emplace_back(thread_worker, settings, scene, &image, &generators, i);
        }

        for (auto& t : threads) {
            t.join();
        }

        const real sample_weight = real(1.0) / real(settings.samples_per_pixel);

        for (uint32 y = 0; y < image.height(); ++y) {
            for (uint32 x = 0; x < image.width(); ++x) {
                image[x][y][0] *= sample_weight;
                image[x][y][1] *= sample_weight;
                image[x][y][2] *= sample_weight;
            }
        }

        return image;
    }

    Image render_scene(const Render_settings& settings, const Scene& scene) {
        return threaded_render(settings, scene);
    }

}
