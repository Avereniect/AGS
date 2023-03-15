#ifndef AGS_ARE_VK_RENDER_QUEUE_HPP
#define AGS_ARE_VK_RENDER_QUEUE_HPP

#include <ags/Graphics_includes.hpp>

#include "Draw_call.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Framebuffer.hpp"

#include <queue>

namespace ags::are::vk_kernel {

    class Render_queue {
    public:

        //=================================================
        // -ctors
        //=================================================

        Render_queue() = default;
        Render_queue(const Render_queue&) = delete;
        Render_queue(Render_queue&&) noexcept;
        ~Render_queue();

        //=================================================
        // Assignment operators
        //=================================================

        Render_queue& operator=(const Render_queue&) = delete;
        Render_queue& operator=(Render_queue&&) noexcept;

        //=================================================
        // Mutators
        //=================================================

        ///
        /// TODO: Add parameter that contains uniforms/alternatives
        ///
        /// Adds drawing command to the render queue
        ///
        /// If any of the specified resources are destroyed before the queue is
        /// submitted then the queue is considered to be invalid and must not be
        /// submitted until its current contents are cleared submitted. Ideally,
        /// this should be avoided in the first place.
        ///
        /// \param mesh Mesh to draw
        /// \param shader Shader to draw mesh with
        /// \param framebuffer Framebuffer to draw to
        void queue_draw_call(
            const Framebuffer& framebuffer,
            const Mesh& mesh,
            const Shader_program& shader
        );

        ///
        /// Performs work that must be done before the queue can be submitted
        ///
        void prepare();

        ///
        /// Clear all previously recorded commands and restore contents of
        /// buffer to empty state.
        ///
        void clear();

        //=================================================
        // Accessors
        //=================================================

        [[nodiscard]]
        vk::CommandBuffer native_handle() const;

    private:

        //=================================================
        // Instance members
        //=================================================

        vk::CommandBuffer command_buffer;

        bool is_recording = false;

    };

}

#endif //AGS_ARE_VK_RENDER_QUEUE_HPP
