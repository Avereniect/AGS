//
// Created by avereniect on 1/21/22.
//

#ifndef AGS_ARE_VK10_SHADER_HPP
#define AGS_ARE_VK10_SHADER_HPP

#include "Includes.hpp"
#include "Enum.hpp"
#include "Framebuffer.hpp"

#include <ags/Types.hpp>
#include <spirv-reflect/spirv_reflect.h>

#include <aul/containers/Multispan.hpp>

#include <string>

namespace ags::are::vk10 {

    struct Vertex_attribute {
        Attribute_type type = Attribute_type::NULL_ATTRIBUTE_TYPE;
        std::uint8_t components = 0;
        std::string name;
    };

    struct Shader_variable {
        Primitive type;
        std::string name;
    };

    /*
    class Shader {
    public:


    protected:

    };

    */

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
        void load_source(std::string_view source);

        ///
        /// Load Spir-V bytecode.
        ///
        /// Instructions in Spir-V have lengths specified in terms of words,
        /// which are defined to be 32-bits in length. Hence the length of the
        /// bytecode is always a multiple of four bytes.
        ///
        /// \param bytecode Span over bytecode for vertex shader
        void load_bytecode(aul::Span<const std::uint32_t> bytecode);

        void unload();

        //=================================================
        // Conversion operators
        //=================================================

        operator bool() const noexcept;

    private:

        //=================================================
        // Instance members
        //=================================================

        vk::ShaderModule module;

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
        void load_source(std::string_view source);

        ///
        /// Load Spir-V bytecode.
        ///
        /// Instructions in Spir-V have lengths specified in terms of words,
        /// which are defined to be 32-bits in length. Hence the length of the
        /// bytecode is always a multiple of four bytes.
        ///
        /// \param bytecode Span over bytecode for fragment shader
        void load_bytecode(aul::Span<const std::uint32_t> bytecode);

    private:

        //=================================================
        // Instance members
        //=================================================

        vk::ShaderModule module;

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
        /// framebuffer similar thereto
        /// \param vs Vertex shader
        /// \param fs Fragment shader
        void compose(const Framebuffer& framebuffer, const Vertex_shader& vs, const Fragment_shader& fs);

        // Release resource held by this object
        void unload();

        //=================================================
        // Conversion operators
        //=================================================

        operator bool() const;

    private:

        //=================================================
        // Static members
        //=================================================

        static int x;

        //=================================================
        // Instance members
        //=================================================

        vk::Pipeline pipeline{};

        //=================================================
        // Helper functions
        //=================================================

    };

}

#endif //AGS_ARE_VK10_SHADER_HPP
