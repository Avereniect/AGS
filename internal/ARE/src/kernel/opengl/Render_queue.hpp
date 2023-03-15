//
// Created by avereniect on 1/12/22.
//

#ifndef AGS_ARE_GL_QUEUE_HPP
#define AGS_ARE_GL_QUEUE_HPP

#include <ags/Graphics_includes.hpp>

#include "../Enums_common.hpp"

#include "Kernel_base.hpp"
#include "Draw_call.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Framebuffer.hpp"
#include "Uniform_pack.hpp"

#include <aul/Span.hpp>

#include <queue>
#include <cstdint>

namespace ags::are::gl_kernel {

    struct Indirect_draw_call {
        GLuint count = 0;
        GLuint instance_count = 0;
        GLuint first_index = 0;
        GLuint base_vertex = 0;
        GLuint base_instance = 0;
    };

    static_assert(sizeof(Indirect_draw_call) == 20);
    static_assert(alignof(Indirect_draw_call) == 4);

    ///
    /// Render queue for OpenGL 4.3 ARE kernel.
    ///
    /// TODO: Consider using indirect buffers
    ///
    class Render_queue : public Kernel_base {
    public:

        //=================================================
        // -ctors
        //=================================================

        ///
        /// \param usage Enum indicating whether contents of queue are meant to
        /// be reused
        explicit Render_queue(Queue_usage usage);

        Render_queue() = default;
        ~Render_queue() = default;

        //=================================================
        // Mutators
        //=================================================

        //TODO: Add support for uniform pack
        ///
        /// Adds a new entry to the render queue
        ///
        /// If any resource held by the paramters called
        ///
        /// \param mesh Mesh object ot draw
        /// \param shader Shader to draw with
        void queue_draw_call(
            const Mesh& mesh,
            const Shader_program& shader
        );

        ///
        /// Sort draw calls to minimize state changes when draw calls are
        /// submitted
        ///
        void prepare();

        //=================================================
        // Accessors
        //=================================================

        ///
        ///
        /// \return Span over draw calls stored within queue
        [[nodiscard]]
        aul::Span<const Draw_call> data() const;

    private:

        //=================================================
        // Instance members
        //=================================================

        std::vector<Draw_call> queue{};

        bool is_prepared = false;
        Queue_usage usage = Queue_usage::SINGLE;

    };

}

#endif //AGS_ARE_GL_QUEUE_HPP
