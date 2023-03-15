#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

//#define AVEL_AVX512BW
//#define AVEL_AVX512VL
//#define AVEL_AVX512F
//#define AVEL_SSE2
//#include <avel/Avel.hpp>

//#define AVML_AVX512BW
//#define AVML_AVX512VL
//#define AVML_AVX512F
//#define AVEL_SSE2
//#include <avml/AVML.hpp>

#include "Engine.hpp"

//TODO: Fix issue if ARE header is included after windowing header when building with OpenGL
#include <ags/Logging.hpp>
#include <ags/Util.hpp>
#include <ags/ui/Windowing.hpp>
#include <ags/ARE.hpp>
#include <ags/apt/APT.hpp>
#include <ags/image/IO.hpp>
#include <ags/mesh/IO.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace ags {

    using ags::image::Pixel_buffer;

    Pixel_buffer<std::uint8_t, 3> read_png(std::string_view path) {
        int x;
        int y;
        int c;

        auto* data = stbi_load(path.data(), &x, &y, &c, 3);
        if (data == nullptr) {
            AGS_WARN("Could not open file \"{}\"", path.data());
            return {};
        }

        if (x == 0 || y == 0) {
            AGS_WARN("Image at location \"{}\" had a zero dimension.", path.data());
            return {};
        }

        Pixel_buffer<std::uint8_t, 3> ret{
            static_cast<std::uint32_t>(x),
            static_cast<std::uint32_t>(y),
            data
        };

        stbi_image_free(data);

        return ret;
    }

    void run() {
        using namespace std::chrono_literals;

        ui::Window win{512, 512, "AGS"};

        Pixel_buffer<std::uint8_t, 3> image = read_png("./assets/textures/scribbles.png");
        are::Texture2D texture{};
        texture.load(image.width(), image.height(), are::Channel_format::XYZ, image.data());

        mesh::Vertex_array vertex_array = mesh::read_vertex_array("./assets/models/suzanne.obj");
        are::Mesh mesh{};
        mesh.load(vertex_array);

        are::Framebuffer framebuffer{};
        framebuffer.specify_attachments(
            win.width(),
            win.height(),
            {
                are::Color_attachment{are::Channel_format::XYZW, Primitive::UINT8}
            },
            are::Depth_format::FLOAT32,
            are::Sample_count::S4
        );

        auto vert_source = read_ascii_text("./assets/shaders/vk/shader.vert");
        //auto vert_source = read_ascii_text("./assets/shaders/glsl43/shader.vert");
        are::Vertex_shader vert_shader{};
        vert_shader.load_glsl(vert_source);

        auto frag_source = read_ascii_text("./assets/shaders/vk/shader.frag");
        //auto frag_source = read_ascii_text("./assets/shaders/glsl43/shader.frag");
        are::Fragment_shader frag_shader{};
        frag_shader.load_glsl(frag_source);

        are::Shader_program shader_program{};
        shader_program.compose(framebuffer, vert_shader, frag_shader);

        are::Render_queue render_queue{};

        while (!win.should_close()) {
            //are::Kernel::poll_errors();
            render_queue.queue_draw_call(framebuffer, mesh, shader_program);
            are::draw(render_queue, framebuffer);

            win.refresh(framebuffer);
            std::this_thread::sleep_for(16ms);
        }
    }

}

int engine_main(int argc, char* argv[]) {
    ags::Engine::init();
    ags::run();
    ags::Engine::term();
    return EXIT_SUCCESS;
}

int sandbox_main(int argc, char* argv[]) {
    return EXIT_SUCCESS;
}

int apt_main(int argc, char* argv[]) {
    namespace apt = ags::apt;
    namespace image = ags::image;

    apt::Camera cam;
    cam.forward = {0.0, 1.0, 0.0};
    cam.up      = {0.0, 0.0, 1.0};

    apt::Scene scene{};
    scene.camera = cam;

    apt::Render_settings settings{};

    settings.samples_per_pixel = 32;

    settings.thread_count = 8;

    settings.image_width = 800;
    settings.image_height = 600;

    auto rendered_image = apt::render_scene(settings, scene);
    auto tone_mapped_image = image::Pixel_buffer<std::uint8_t, 3>{rendered_image.width(), rendered_image.height()};

    //TODO: Actual tone-mapping before conversion
    for (std::uint32_t j = 0; j < rendered_image.height(); ++j) {
        for (std::uint32_t i = 0; i < rendered_image.width(); ++i) {
            for (std::uint32_t k = 0; k < 3; ++k) {
                float c = std::max(0.0f, std::min(1.0f, rendered_image[i][j][k]));
                tone_mapped_image[i][j][k] = static_cast<std::uint8_t>(c * 255.0f);
            }
        }
    }

    ags::image::write_png(tone_mapped_image, "image.png");

    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
    //return apt_main(argc, argv);
    return engine_main(argc, argv);
}
