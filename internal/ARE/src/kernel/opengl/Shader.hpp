#ifndef AGS_ARE_GL_SHADER_HPP
#define AGS_ARE_GL_SHADER_HPP

#include <ags/Graphics_includes.hpp>

#include "Object.hpp"
#include "Framebuffer.hpp"

#include <string>

#include <aul/containers/Array_map.hpp>

namespace ags::are::gl_kernel {

    struct Uniform {
        Uniform_type type;
        std::uint16_t length = 0;
    };

    class Compute_shader : public Object {
    public:

        //=================================================
        // -ctors
        //=================================================

        Compute_shader() = default;
        Compute_shader(const Compute_shader&) = delete;
        Compute_shader(Compute_shader&&) noexcept;
        ~Compute_shader();

        //=================================================
        // Assignment operators
        //=================================================

        Compute_shader& operator=(const Compute_shader&) = delete;
        Compute_shader& operator=(Compute_shader&&) noexcept;

        //=================================================
        // Resource mutators
        //=================================================

        ///
        /// Any pre-existing resource is released
        ///
        /// If this fails for any reason, this resource does not hold a resource
        ///
        /// \param source GLSL compute shader source code
        void load_glsl(std::string_view source);

        ///
        ///
        /// \param bytecode
        void load_spirv(aul::Span<const std::uint32_t> bytecode);

        ///
        /// Any pre-existing resource is released
        ///
        /// If this fails for any reason, this resource does not hold a resource
        ///
        /// \param shader_binary Cached shader binary information
        void load_cached_binary(aul::Span<const std::byte> shader_binary);

        //=================================================
        // Accessors
        //=================================================

        ///
        /// \return Pair containing binary format id and vector containing
        /// shader binary
        [[nodiscard]]
        std::vector<std::byte> retrieve_shader_binary() const;

        ///
        /// \return
        [[nodiscard]]
        std::array<std::uint32_t, 3> work_group_dimensions() const;

    private:

        //=================================================
        // Instance members
        //=================================================

        GLuint shader_id;

        std::array<std::uint32_t, 3> work_group_dims{};

        //=================================================
        // Helper functions
        //=================================================

        void query_work_group_dimensions();

    };

    class Vertex_shader : public Object {
    public:

        Vertex_shader() = default;

        //=================================================
        // Resource mutators
        //=================================================

        ///
        /// Load GLSL source code
        ///
        /// Discards any previously held resource.
        ///
        /// If failure occurs for any reason, the truthiness of this object is
        /// false.
        ///
        /// \param source String view over string representing source code for
        /// fragment shader
        void load_glsl(std::string_view source);

        ///
        /// Load Spir-V bytecode.
        ///
        /// Discards any previously held resource
        ///
        /// If failure occurs for any reason, this object will not hold a
        /// resource.
        ///
        /// Instructions in Spir-V have lengths specified in terms of words,
        /// which are defined to be 32-bits in length. Hence the length of the
        /// bytecode is always a multiple of four bytes.
        ///
        /// \param bytecode Span over bytecode for fragment shader
        void load_spirv(aul::Span<const std::uint32_t> bytecode);

    private:

    };

    class Fragment_shader : public Object {
    public:

        Fragment_shader() = default;

        //=================================================
        // Resource mutators
        //=================================================

        ///
        /// Load GLSL source code
        ///
        /// Discards any previously held resource.
        ///
        /// If failure occurs for any reason, the truthiness of this object is
        /// false.
        ///
        /// \param source String view over string representing source code for
        /// fragment shader
        void load_glsl(std::string_view source);

        ///
        /// Load Spir-V bytecode.
        ///
        /// Discards any previously held resource
        ///
        /// If failure occurs for any reason, this object will not hold a
        /// resource.
        ///
        /// Instructions in Spir-V have lengths specified in terms of words,
        /// which are defined to be 32-bits in length. Hence the length of the
        /// bytecode is always a multiple of four bytes.
        ///
        /// \param bytecode Span over bytecode for fragment shader
        void load_spirv(aul::Span<const std::uint32_t> bytecode);

    private:

    };

    class Geometry_shader {

    };

    class Tesselation_shader {

    };

    class Shader_program : public Object {
    public:

        //=================================================
        // -ctors
        //=================================================

        Shader_program() = default;
        Shader_program(const Shader_program&) = delete;
        Shader_program(Shader_program&&);
        ~Shader_program();

        //=================================================
        // Assignment operators
        //=================================================

        Shader_program& operator=(const Shader_program&) = delete;
        Shader_program& operator=(Shader_program&&);

        //=================================================
        // Resource mutators
        //=================================================

        ///
        /// \param framebuffer Framebuffer to which shader will render to, or
        /// framebuffer with compatible format
        /// \param vs Vertex shader
        /// \param fs Fragment shader
        void compose(
            const Framebuffer& framebuffer,
            const Vertex_shader& vs,
            const Fragment_shader& fs
        );
        
        void compose(
            const Framebuffer& framebuffer,
            const Vertex_shader& vs,
            const Tesselation_shader& ts,
            const Fragment_shader& fs
        );
        
        void compose(
            const Framebuffer& framebuffer,
            const Vertex_shader& vs,
            const Geometry_shader& gs,
            const Fragment_shader& fs
        );
        
        void compose(
            const Framebuffer& framebuffer,
            const Vertex_shader& vs,
            const Tesselation_shader& ts,
            const Geometry_shader& gs,
            const Fragment_shader& fs
        );
        
        ///
        /// Any pre-existing resource is released
        ///
        /// If this fails for any reason, this resource does not hold a resource
        ///
        /// \param shader_binary Shader binary
        void load_program_binary(aul::Span<const std::byte> shader_binary);

        //=================================================
        // Accessors
        //=================================================

        ///
        /// \return Pair containing binary format id and vector containing
        /// shader binary
        [[nodiscard]]
        std::vector<std::byte> retrieve_shader_binary() const;

    private:

        //=================================================
        // Instance members
        //=================================================

        ///
        /// Map associating attribute locations to the type occupying it
        ///
        aul::Array_map<std::uint32_t, Attribute_type> attribute_inputs{};

        ///
        /// Map associating uniform locations to the type occupying it
        ///
        aul::Array_map<std::uint32_t, Uniform_type> uniform_inputs{};

        ///
        /// Map associating uniform names to their location
        ///
        aul::Array_map<std::string, std::uint32_t> uniform_locations{};

        ///
        /// Map associating framebuffer locations to the format occupying that
        /// location
        ///
        aul::Array_map<std::uint32_t, Texture_format> framebuffer_outputs;

        //=================================================
        // Helper functions
        //=================================================

        ///
        /// Populate attribute_inputs
        ///
        void query_attributes();

        ///
        /// Populate uniform_inputs
        ///
        void query_uniforms();

        ///
        /// Populate uniform_locations
        ///
        void query_uniform_blocks();

        ///
        /// Populate framebuffer_outputs
        ///
        void query_framebuffer_outputs();

    };

}

#endif //AGS_ARE_GL_SHADER_HPP
