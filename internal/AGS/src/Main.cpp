#include <iostream>

#include <cstdlib>

#define AVEL_AVX512BW
#define AVEL_AVX512VL
#define AVEL_AVX512F
#include <avel/Avel.hpp>

#define AVML_AVX512BW
#define AVML_AVX512VL
#define AVML_AVX512F
#include <avml/AVML.hpp>

#include "Engine.hpp"

#include <ags/ui/Windowing.hpp>

#include <spirv-reflect/spirv_reflect.h>

namespace ags {

    void run() {
        ui::Window win{800, 600, "Hello"};

        while (!win.should_close()) {

            win.refresh();
            Windowing_context::poll_events();
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
    std::string shader_bytecode_path{"/mnt/hard_disk/Technology/Repos/AGS/assets/shaders/glsl43/shaderf.spv"};

    std::FILE* file = fopen(shader_bytecode_path.c_str(), "r");
    if (!file) {
        std::cerr << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    fseek(file, 0l, SEEK_END);
    std::size_t file_size = ftell(file);
    rewind(file);

    std::vector<std::uint32_t> bytecode{};
    bytecode.resize(file_size / 4);

    fread(bytecode.data(), sizeof(std::uint32_t), bytecode.size(), file);


    SpvReflectShaderModule reflect_module;
    SpvReflectResult result = spvReflectCreateShaderModule(
        bytecode.size() * sizeof(std::uint32_t),
        bytecode.data(),
        &reflect_module
    );

    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
    return sandbox_main(argc, argv);
    //return engine_main(argc, argv);
}
