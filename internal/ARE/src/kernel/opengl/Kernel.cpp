//
// Created by avereniect on 1/9/22.
//
#include "Kernel.hpp"

namespace ags::are::gl_kernel {

    //=================================================
    // Static members
    //=================================================

    //=================================================
    // State members
    //=================================================

    void Kernel::init() {
        Kernel_base::init();
        Mesh_kernel::init();
        Texture_kernel::init();
        Shader_kernel::init();
        Framebuffer_kernel::init();
    }

    void Kernel::term() {
        Framebuffer_kernel::term();
        Shader_kernel::term();
        Texture_kernel::term();
        Mesh_kernel::term();
        Kernel_base::term();
    }

    //=================================================
    // State mutators
    //=================================================

    //=================================================
    // Drawing methods
    //=================================================

    void Kernel::submit_render_queue(
        Render_queue& render_queue,
        GLuint framebuffer_id,
        attachment_mask_type attachment_mask,
        std::array<std::uint32_t, 2> dims
    ) {
        //TODO: Make clearing optional/replace with more advanced system

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.25, 0.50f, 0.75f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        render_queue.prepare();

        activate_color_attachments(attachment_mask);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);
        for (auto& draw_call :  render_queue.data()) {
            glViewport(0, 0, dims[0], dims[1]);
            glUseProgram(draw_call.shader);
            glBindVertexArray(draw_call.vao);

            //TODO: Handle textures, uniforms
            glDrawElements(GL_TRIANGLES, GLsizei(draw_call.num_indices), GL_UNSIGNED_INT, nullptr);
        }
    }

    void Kernel::submit_compute_queue(Compute_queue& compute_queue) {
        //TODO: Implement
    }

}
