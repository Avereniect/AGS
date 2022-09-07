//
// Created by avereniect on 1/13/22.
//
#include "Render_queue.hpp"

namespace ags::are::gl_kernel {

    //=====================================================
    // -ctors
    //=====================================================

    Render_queue::Render_queue(Queue_usage usage):
        queue(),
        is_prepared(false),
        usage(usage) {}

    //=====================================================
    // Mutators
    //=====================================================

    void Render_queue::queue_draw_call(
        const Mesh& mesh,
        const Shader_program& shader
    ) {
        is_prepared = false;

        queue.emplace_back(Draw_call{
            mesh.index_count(),
            mesh.native_handle(),
            shader.native_handle()
        });
    }

    void Render_queue::prepare() {
        if (is_prepared) {
            return;
        }

        std::sort(queue.begin(), queue.end());
        is_prepared = true;
    }

    //=====================================================
    // Accessors
    //=====================================================

    aul::Span<const Draw_call> Render_queue::data() const {
        return {queue.data(), queue.size()};
    }

}
