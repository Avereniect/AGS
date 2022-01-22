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

#include <ags/Vulkan_core.hpp>
#include <ags/Window_core.hpp>
#include <ags/ui/Windowing.hpp>

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

int main(int argc, char* argv[]) {
    return engine_main(argc, argv);
}
