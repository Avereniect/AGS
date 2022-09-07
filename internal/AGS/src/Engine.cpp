//
// Created by avereniect on 12/11/21.
//

#include "Engine.hpp"

#include "../../AGS_core/src/Windowing_context.hpp"
#include <ags/ARE.hpp>

#include <cstdlib>

namespace ags {

    void Engine::init() {
        std::atexit([] () {
            ags::Engine::term();
        });

        ags::Windowing_context::init();
        are::ARE::init();
    }

    void Engine::term() {
        are::ARE::term();
        Windowing_context::term();
    }

}
