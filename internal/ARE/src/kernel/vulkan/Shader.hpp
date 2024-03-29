#ifndef AGS_ARE_VK_SHADER_HPP
#define AGS_ARE_VK_SHADER_HPP

#include <ags/Graphics_includes.hpp>

#include "Enums.hpp"
#include "Framebuffer.hpp"

#include <ags/Types.hpp>

#include <aul/Span.hpp>

#include <string>

namespace ags::are::vk_kernel {

    class Compute_shader {
    public:


    protected:

    };

    class Shader_program;

    class Vertex_shader {
    public:

        friend class Shader_program;

        //=================================================
        // -ctors
        //=================================================

        Vertex_shader();
        Vertex_shader(const Vertex_shader&) = delete;
        Vertex_shader(Vertex_shader&&) noexcept;
        ~Vertex_shader();

        //=================================================
        // Assignment operators
        //=================================================

        Vertex_shader& operator=(const Vertex_shader&) = delete;
        Vertex_shader& operator=(Vertex_shader&&) noexcept;

        //=================================================
        // Resource mutators
        //=================================================

        ///
        /// Load GLSL source code
        ///
        /// The GLSL source code passed to this function should be 330 or newer
        ///
        /// \param source String view over string representing source code for
        /// vertex shader
        void load_glsl(std::string_view source);

        ///
        /// Load Spir-V bytecode.
        ///
        /// Instructions in Spir-V have lengths specified in terms of words,
        /// which are defined to be 32-bits in length. Hence the length of the
        /// bytecode is always a multiple of four bytes.
        ///
        /// \param bytecode Span over bytecode for vertex shader
        void load_spirv(aul::Span<const std::uint32_t> bytecode);

        ///
        /// Release resource held by this object
        ///
        void unload();

        //=================================================
        // Conversion operators
        //=================================================

        ///
        /// \return true if the object currently holds a resource and false
        /// otherwise
        operator bool() const noexcept;

    private:

        //=================================================
        // Instance members
        //=================================================

        vk::ShaderModule shader_module;

        #if defined(AGS_ARE_VK10_DEBUG)
        std::unique_ptr<SpvReflectShaderModule> reflect_data;
        #endif

        //=================================================
        // Helper functions
        //=================================================

        #if defined(AGS_ARE_VK10_DEBUG)
        static void retrieve_module_metadata(const void* data, std::size_t n);
        #endif

    };

    class Fragment_shader {
    public:

        friend class Shader_program;

        //=================================================
        // -ctors
        //=================================================

        Fragment_shader();
        Fragment_shader(const Fragment_shader&) = delete;
        Fragment_shader(Fragment_shader&&) noexcept;
        ~Fragment_shader();

        //=================================================
        // Assignment operators
        //=================================================

        Fragment_shader& operator=(const Fragment_shader&) = delete;
        Fragment_shader& operator=(Fragment_shader&&) noexcept;

        //=================================================
        // Resource mutators
        //=================================================

        ///
        /// Load GLSL source code
        ///
        /// The GLSL source code passed to this function should be 330 or newer
        ///
        /// \param source String view over string representing source code for
        /// fragment shader
        void load_glsl(std::string_view source);

        ///
        /// Load Spir-V bytecode.
        ///
        /// Instructions in Spir-V have lengths specified in terms of words,
        /// which are defined to be 32-bits in length. Hence the length of the
        /// bytecode is always a multiple of four bytes.
        ///
        /// \param bytecode Span over bytecode for fragment shader
        void load_spirv(aul::Span<const std::uint32_t> bytecode);

        ///
        /// Release resource held by this object
        ///
        void unload();

        //=================================================
        // Conversion operators
        //=================================================

        ///
        /// \return true if the object currently holds a resource and false
        /// otherwise
        operator bool() const noexcept;

    private:

        //=================================================
        // Instance members
        //=================================================

        vk::ShaderModule shader_module;

        #if defined(AGS_ARE_VK10_DEBUG)
        std::unique_ptr<SpvReflectShaderModule> reflect_data;
        #endif

        //=================================================
        // Helper functions
        //=================================================

        #if defined(AGS_ARE_VK10_DEBUG)
        static void retrieve_module_metadata(const void* data, std::size_t n);
        #endif

    };



    class Shader_program {
    public:

        //=================================================
        // -ctors
        //=================================================

        Shader_program() = default;
        Shader_program(const Shader_program&) = delete;
        Shader_program(Shader_program&&) noexcept;
        ~Shader_program();

        //=================================================
        // Assignment operators
        //=================================================

        Shader_program& operator=(const Shader_program&) = delete;
        Shader_program& operator=(Shader_program&&) noexcept;

        //=================================================
        // Resource mutator
        //=================================================

        //void load(const std::string& vert_src, const std::string& frag_src);

        ///
        /// \param framebuffer Framebuffer to which shader will render to, or
        /// framebuffer with compatible formats
        /// \param vs Vertex shader
        /// \param fs Fragment shader
        void compose(const Framebuffer& framebuffer, const Vertex_shader& vs, const Fragment_shader& fs);

        ///
        /// Release resource held by this object
        ///
        void unload();

        ///
        /// \return
        vk::Pipeline native_handle() const;

        //=================================================
        // Conversion operators
        //=================================================

        [[nodiscard]]
        operator bool() const;

    private:

        //=================================================
        // Instance members
        //=================================================

        vk::Pipeline pipeline{};

        vk::PipelineLayout pipeline_layout{};

        //=================================================
        // Helper functions
        //=================================================

    };

}

#endif //AGS_ARE_VK_SHADER_HPP
