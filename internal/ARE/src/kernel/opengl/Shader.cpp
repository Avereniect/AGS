#include "Shader.hpp"
#include "Shader_kernel.hpp"

#include <ags/Logging.hpp>

namespace ags::are::gl_kernel {

    //=========================================================================
    // Compute_shader
    //=========================================================================

    Compute_shader::Compute_shader(Compute_shader&& other) noexcept:
        Object(std::move(other)),
        shader_id(std::exchange(other.shader_id, 0)) {}

    Compute_shader::~Compute_shader() {
        if (id) {
            glDeleteShader(id);
        }
    }

    Compute_shader& Compute_shader::operator=(Compute_shader&& rhs) noexcept {
        Object::operator=(std::move(rhs));
        shader_id = std::exchange(rhs.shader_id, 0);
        return *this;
    }

    void Compute_shader::load_glsl(std::string_view source) {
        shader_id = Shader_kernel::acquire_compute_shader();

        const char* source_data = source.data();
        const GLint length = source.size();
        glShaderSource(shader_id, 1, &source_data, &length);
        glCompileShader(shader_id);

        {
            GLint success;
            glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
            if (!success) {
                std::basic_string<GLchar> buffer;
                buffer.resize(4 * 1024);
                glGetShaderInfoLog(shader_id, buffer.size(), nullptr, buffer.data());

                Shader_kernel::release_compute_shader(shader_id);
                shader_id = 0;

                AGS_ERROR("Error when compiling compute shader:\n{}", buffer.data());
                return;
            }
        }

        id = Shader_kernel::acquire_shader_program();
        glAttachShader(id, shader_id);
        glLinkProgram(id);
        glDetachShader(id, shader_id);

        {
            GLint success;
            glGetProgramiv(id, GL_LINK_STATUS, &success);
            if (!success) {
                std::basic_string<GLchar> buffer;
                buffer.resize(4 * 1024);
                glGetShaderInfoLog(id, buffer.size(), nullptr, buffer.data());

                Shader_kernel::release_shader_program(id);
                id = 0;

                AGS_ERROR("Error when linking compute shader.", buffer.data());
                return;
            }
        }

        query_work_group_dimensions();
    }

    void Compute_shader::load_cached_binary(aul::Span<const std::byte> shader_binary) {
        if (!id) {
            id = Shader_kernel::acquire_shader_program();
        }

        GLenum binary_format_id;
        std::memcpy(&binary_format_id, shader_binary.data(), sizeof(GLenum));

        glProgramBinary(
            id,
            binary_format_id,
            reinterpret_cast<const void*>(shader_binary.data() + sizeof(GLenum)),
            GLsizei(shader_binary.size() - sizeof(GLenum))
        );

        GLint success;
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success) {
            std::basic_string<GLchar> buffer;
            buffer.resize(4 * 1024);
            glGetShaderInfoLog(id, buffer.size(), nullptr, buffer.data());
            AGS_ERROR("Error when loading shader program binary.", buffer.data());

            Shader_kernel::release_shader_program(id);
            id = 0;

            return;
        }

        query_work_group_dimensions();
    }

    std::vector<std::byte> Compute_shader::retrieve_shader_binary() const {
        if (!id) {
            return {};
        }

        GLint binary_length;
        glGetProgramiv(id, GL_PROGRAM_BINARY_LENGTH, &binary_length);

        std::vector<std::byte> program_binary;
        program_binary.resize(binary_length + sizeof(GLenum));

        GLsizei read_length;
        GLenum binary_id;
        glGetProgramBinary(
            id,
            GLsizei(program_binary.size()),
            &read_length,
            &binary_id,
            program_binary.data()
        );

        std::memcpy(program_binary.data(), &binary_id, sizeof(GLenum));

        return program_binary;
    }

    std::array<std::uint32_t, 3> Compute_shader::work_group_dimensions() const {
        return work_group_dims;
    }

    void Compute_shader::query_work_group_dimensions() {
        std::array<GLint, 3> tmp_dims;
        glGetProgramiv(id, GL_COMPUTE_WORK_GROUP_SIZE, tmp_dims.data());
        work_group_dims[0] = tmp_dims[0];
        work_group_dims[1] = tmp_dims[1];
        work_group_dims[2] = tmp_dims[2];
    }

    //=========================================================================
    // Vertex shader
    //=========================================================================

    void Vertex_shader::load_glsl(std::string_view source) {
        if (id) {
            Shader_kernel::release_vertex_shader(id);
        }

        const char* data = source.data();
        const GLint length = source.size();
        id = Shader_kernel::acquire_vertex_shader();

        glShaderSource(id, 1, &data, &length);
        glCompileShader(id);

        GLint success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if(!success) {
            std::basic_string<GLchar> buffer;
            buffer.resize(4 * 1024);
            glGetShaderInfoLog(id, buffer.size(), nullptr, buffer.data());

            Shader_kernel::release_vertex_shader(id);
            id = 0;

            AGS_ERROR("Error when compiling vertex shader:\n{}", buffer.data());
            return;
        }
    }

    void Vertex_shader::load_spirv(aul::Span<const std::uint32_t> bytecode) {
        id = Shader_kernel::acquire_vertex_shader();
        glShaderBinary(
            1, &id,
            GL_SHADER_BINARY_FORMAT_SPIR_V,
            bytecode.data(),
            GLsizei(sizeof(std::uint32_t) * bytecode.size())
        );

        //TODO: Complete implementation
    }

    //=========================================================================
    // Fragment shader
    //=========================================================================

    void Fragment_shader::load_glsl(std::string_view source) {
        const char* data = source.data();
        const GLint length = source.size();
        id = Shader_kernel::acquire_fragment_shader();

        glShaderSource(id, 1, &data, &length);
        glCompileShader(id);

        GLint success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if(!success) {
            std::basic_string<GLchar> buffer;
            buffer.resize(4 * 1024);
            glGetShaderInfoLog(id, buffer.size(), nullptr, buffer.data());

            Shader_kernel::release_fragment_shader(id);
            id = 0;

            AGS_ERROR("Error when compiling fragment shader:\n{}", buffer.data());
            return;
        }
    }

    //=========================================================================
    // Shader_program
    //=========================================================================

    Shader_program::~Shader_program() {
        Shader_kernel::release_shader_program(id);
    }

    void Shader_program::compose(const Framebuffer& framebuffer, const Vertex_shader& vs, const Fragment_shader& fs) {
        id = Shader_kernel::acquire_shader_program();

        glAttachShader(id, vs.native_handle());
        glAttachShader(id, fs.native_handle());
        glLinkProgram(id);
        glDetachShader(id, vs.native_handle());
        glDetachShader(id, fs.native_handle());

        GLint success;
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success) {
            std::basic_string<GLchar> buffer;
            buffer.resize(4 * 1024);
            glGetShaderInfoLog(id, buffer.size(), nullptr, buffer.data());

            AGS_ERROR("Error when linking shader program:\n{}", buffer.data());

            Shader_kernel::release_shader_program(id);
            id = 0;

            return;
        }

        //TODO: Consider forcing shader compilation ahead of time by making
        // a simple draw call

        query_attributes();
        query_uniforms();
        query_uniform_blocks();
        query_framebuffer_outputs();
    }

    void Shader_program::load_program_binary(aul::Span<const std::byte> shader_binary) {
        if (!id) {
            id = Shader_kernel::acquire_shader_program();
        }

        GLenum binary_format_id;
        std::memcpy(&binary_format_id, shader_binary.data(), sizeof(GLenum));

        glProgramBinary(
            id,
            binary_format_id,
            reinterpret_cast<const void*>(shader_binary.data() + sizeof(GLenum)),
            GLsizei(shader_binary.size() - sizeof(GLenum))
        );

        GLint success;
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success) {
            std::basic_string<GLchar> buffer;
            buffer.resize(4 * 1024);
            glGetShaderInfoLog(id, buffer.size(), nullptr, buffer.data());
            AGS_ERROR("Error when loading shader program binary.", buffer.data());

            Shader_kernel::release_shader_program(id);
            id = 0;

            return;
        }

        query_attributes();
        query_uniforms();
        query_uniform_blocks();
        query_framebuffer_outputs();
    }

    std::vector<std::byte> Shader_program::retrieve_shader_binary() const {
        if (!id) {
            return {};
        }

        GLint binary_length;
        glGetProgramiv(id, GL_PROGRAM_BINARY_LENGTH, &binary_length);

        std::vector<std::byte> program_binary;
        program_binary.resize(binary_length + sizeof(GLenum));

        GLsizei read_length;
        GLenum binary_id;
        glGetProgramBinary(
            id,
            GLsizei(program_binary.size()),
            &read_length,
            &binary_id,
            program_binary.data() + sizeof(GLenum)
        );

        return program_binary;
    }

    void Shader_program::query_attributes() {
        GLint attribute_count = 0;
        glGetProgramiv(id, GL_ACTIVE_ATTRIBUTES, &attribute_count);
        for (GLint i = 0; i < attribute_count; ++i) {

            GLsizei buffer_size = 1024;
            GLchar buffer[buffer_size];

            GLsizei length;
            GLint size;
            GLenum type;

            glGetActiveAttrib(
                id,
                i,
                buffer_size,
                &length,
                &size,
                &type,
                buffer
            );

            attribute_inputs.emplace(
                glGetAttribLocation(id, buffer),
                to_attribute_type(type)
            );
        }
    }

    void Shader_program::query_uniforms() {
        GLint uniform_count= 0;
        glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &uniform_count);

        for (GLint i = 0; i < uniform_count; ++i) {
            GLsizei buffer_size = 1024;
            GLchar buffer[buffer_size];

            GLsizei length = 0;

            GLint size;
            GLenum type;

            glGetActiveUniform(
                id,
                i,
                buffer_size,
                &length,
                &size,
                &type,
                buffer
            );

            std::uint32_t location = glGetUniformLocation(id, buffer);

            uniform_inputs.emplace(
                location,
                to_uniform_type(type)
            );

            uniform_locations.emplace(
                std::string(buffer),
                location
            );
        }
    }

    void Shader_program::query_uniform_blocks() {
        //TODO: Implement

    }

    void Shader_program::query_framebuffer_outputs() {
        //TODO: Implement
    }

}
