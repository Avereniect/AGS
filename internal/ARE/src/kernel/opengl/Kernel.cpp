//
// Created by avereniect on 1/9/22.
//
#include "Kernel.hpp"

namespace ags::are::gl33 {

    std::priority_queue<Draw_call> Kernel::render_queue{};

    bool Kernel::init() {
        return true;
    }

    void Kernel::term() {

    }

    //=================================================
    // Drawing methods
    //=================================================

    void Kernel::queue_frame(const Mesh& mesh, const Shader& shader) {

    }

    void Kernel::draw_frame() {
        while (!render_queue.empty()) {
            const auto& draw_call = render_queue.top();
            issue_draw_call(draw_call);
        }

        //TODO: Clean up unused resources
    }

    void issue_draw_call(const Draw_call& draw_call) {
        //TODO:
        //Bind Shader
        //Bind Mesh
        //Specify uniforms

        glDrawElements(GL_TRIANGLES, draw_call.num_elements, GL_UNSIGNED_INT, nullptr);
        //TODO: Poll for errors.
    }

}