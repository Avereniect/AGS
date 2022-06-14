//
// Created by avereniect on 12/22/21.
//

#include "Common.hpp"
#include "Render.hpp"

#include "Intersection.hpp"
#include "Random.hpp"

#include <iostream>

#include <aul/Math.hpp>

#include <thread>

namespace ags::apt {

    color evaluate_world(uvec3r dir) {
        const uvec3r peak = avml::assume_normalized({0.0, 1.0, 0.0});

        const color black{0.0, 0.0, 0.0};
        return color{0.25, 0.50, 0.75} * avml::dot(dir, peak);
    }

    color trace_path(vec3r origin, uvec3r dir) {
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
        std::uint32_t thread_index
    ) {
        //Compute range of pixels that need to be computed
        Image& image = *img;

        const auto image_pixel_count = settings.image_width * settings.image_height;
        const auto thread_pixel_count = aul::divide_ceil(image_pixel_count, settings.thread_count);

        uvec3r camera_z = -scene.camera.forward;
        uvec3r camera_y = scene.camera.up;
        uvec3r camera_x = avml::cross(camera_y, camera_z);

        real sensor_width = 0.0f;
        real sensor_height = 0.0;

        if (image.width() < image.height()) {
            sensor_height = scene.camera.sensor_size;
            sensor_width = scene.camera.sensor_size * float(image.width()) / float(image.height());
        } else {
            sensor_height = scene.camera.sensor_size * float(image.height()) / float(image.width());
            sensor_width = scene.camera.sensor_size;
        }

        uint32 i = 0;
        for (uint32 y = 0; y < image.height(); ++y) {
            for (uint32 x = 0; x < image.width(); ++x, ++i)  {
                i %= settings.thread_count;

                if (i % settings.thread_count != thread_index) {
                    continue;
                }

                //TODO: Vectorize this
                const auto x_numer = +static_cast<int32>((x - image.width())  + x + 1);
                const auto y_numer = -static_cast<int32>((y - image.height()) + y + 1);

                //TODO: Add support for multi-sampling

                color c = {0.0, 0.0, 0.0};
                for (uint32 s = 0; s < settings.samples_per_pixel; ++s) {
                    real sample_offset_x = 0.0;
                    real sample_offset_y = 0.0;

                    if (settings.pixel_filter == Pixel_filter::GAUSSIAN) {
                        auto rand_xy = normal_random((x + 9340539) * (y + 18) * (s + 348));

                        //Multiplication by 1.0/3.5 narrows approximate range of most random normal values to [-1, 1] range

                        sample_offset_x = settings.pixel_filter_width * rand_xy[0] * (1.0 / 3.5);
                        sample_offset_y = settings.pixel_filter_width * rand_xy[1] * (1.0 / 3.5);
                    } else {
                        sample_offset_x = settings.pixel_filter_width * uniform_random_n1_p1(x * x * (y + s));
                        sample_offset_y = settings.pixel_filter_width * uniform_random_n1_p1((x + s) * y * y);
                    }

                    //const real sample_offset_x = settings.pixel_filter_width * uniform_random_n1_p1(x * x * (y + s));
                    //const real sample_offset_y = settings.pixel_filter_width * uniform_random_n1_p1((x + s) * y * y);

                    const real x_ndc = (x_numer + sample_offset_x) / real(image.width()) + scene.camera.offset[0];
                    const real y_ndc = (y_numer + sample_offset_y) / real(image.height()) + scene.camera.offset[1];

                    //Sensor size might be off by a factor of 2
                    const uvec3r dir = avml::normalize(
                        camera_x * x_ndc * sensor_width
                        + camera_y * y_ndc * sensor_height
                        - camera_z * scene.camera.focal_length
                    );

                    c += trace_path(scene.camera.location, dir);
                }

                image[x][y] = Image::pixel_type{c[0], c[1], c[2]};
            }
        }
    }

    Image threaded_render(const Render_settings& settings, const Scene& scene) {
        if (settings.thread_count== 0) {
            //TODO: Default to hardware concurrency.
        }

        std::uint32_t thread_count = (settings.thread_count == 0) ? std::thread::hardware_concurrency() : settings.thread_count;

        std::vector<Image> images{};
        images.reserve(settings.thread_count);
        for (std::uint32_t i = 0; i < settings.thread_count; ++i) {
            images.emplace_back(settings.image_width, settings.image_height);
        }

        std::vector<std::thread> threads;
        for (std::uint32_t i = 0; i < settings.thread_count; ++i) {
            threads.emplace_back(thread_worker, settings, scene, images.data() + i, i);
        }

        for (auto& t : threads) {
            t.join();
        }

        const real sample_weight = real(1.0) / real(settings.samples_per_pixel);

        for (uint32 i = 1; i < settings.thread_count; ++i) {
            for (uint32 y = 0; y < images[i].width(); ++y) {
                for (uint32 x = 0; x < images[i].height(); ++x) {
                    images[0][x][y][0] += images[i][x][y][0];
                    images[0][x][y][1] += images[i][x][y][1];
                    images[0][x][y][2] += images[i][x][y][2];
                }
            }
        }

        for (uint32 y = 0; y < images[0].height(); ++y) {
            for (uint32 x = 0; x < images[0].width(); ++x) {
                images[0][x][y][0] *= sample_weight;
                images[0][x][y][1] *= sample_weight;
                images[0][x][y][2] *= sample_weight;
            }
        }

        return images[0];
    }

    Image render_scene(const Render_settings& settings, const Scene& scene) {
        return threaded_render(settings, scene);
    }

}
