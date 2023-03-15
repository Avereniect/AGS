#include "Shader.hpp"
#include "Shader_kernel.hpp"
#include "Kernel.hpp"

#include <glslang/Include/glslang_c_interface.h>

#include <glslang/Public/ShaderLang.h>
#include <glslang/Public/ResourceLimits.h>
#include <glslang/SPIRV/GlslangToSpv.h>

#include <stdexcept>

namespace ags::are::vk_kernel {

    //=========================================================================
    // Vertex Shader Object
    //=========================================================================

    Vertex_shader::Vertex_shader():
        shader_module(VK_NULL_HANDLE) {}

    Vertex_shader::Vertex_shader(Vertex_shader&& vs) noexcept:
        shader_module(std::exchange(vs.shader_module, VK_NULL_HANDLE)) {}

    Vertex_shader::~Vertex_shader() {
        Device_kernel::get_graphics_device().handle.destroyShaderModule(shader_module);

        #if defined(AGS_ARE_VK10_DEBUG)
        spvReflectDestroyShaderModule(reflect_data.get());
        #endif
    }

    Vertex_shader& Vertex_shader::operator=(Vertex_shader&& rhs) noexcept {
        shader_module = std::exchange(rhs.shader_module, VK_NULL_HANDLE);
        return *this;
    }

    void Vertex_shader::load_glsl(std::string_view source) {
        //TODO: Populate resource according to hardware capabilities
        glslang_limits_t limits{
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true
        };

        glslang_resource_t resource{
            32,
            6,
            32,
            32,
            64,
            4096,
            64,
            32,
            80,
            32,
            4096,
            32,
            128,
            8,
            16,
            16,
            15,
            -8,
            7,
            8,
            65535,
            65535,
            65535,
            1024,
            1024,
            64,
            1024,
            16,
            8,
            8,
            1,
            60,
            64,
            64,
            128,
            128,
            8,
            8,
            8,
            0,
            0,
            0,
            0,
            0,
            8,
            8,
            16,
            256,
            1024,
            1024,
            64,
            128,
            128,
            16,
            1024,
            4096,
            128,
            128,
            16,
            1024,
            120,
            32,
            64,
            16,
            0,
            0,
            0,
            0,
            8,
            8,
            1,
            0,
            0,
            0,
            0,
            1,
            1,
            16384,
            4,
            64,
            8,
            8,
            4,
            256,
            512,
            32,
            1,
            1,
            32,
            1,
            1,
            4,
            256,
            256,
            128,
            128,
            128,
            128,
            128,
            128,
            4,
            1,
            limits
        };

        const glslang_input_t input {
            GLSLANG_SOURCE_GLSL,
            GLSLANG_STAGE_VERTEX,
            GLSLANG_CLIENT_VULKAN,
            GLSLANG_TARGET_VULKAN_1_0,
            GLSLANG_TARGET_SPV,
            GLSLANG_TARGET_SPV_1_0,
            source.data(),
            100,
            GLSLANG_CORE_PROFILE,
            false,
            false,
            GLSLANG_MSG_DEFAULT_BIT,
            &resource
        };

        glslang_shader_t* shader = glslang_shader_create(&input);

        if (!glslang_shader_preprocess(shader, &input)) {
            AGS_ERROR("Error in GLSL to Spir-V conversion:");
            AGS_ERROR("{}", glslang_shader_get_info_log(shader));
            AGS_ERROR("{}", glslang_shader_get_info_debug_log(shader));
            glslang_shader_delete(shader);
            return;
        }

        if (!glslang_shader_parse(shader, &input)) {
            AGS_ERROR("Error in GLSL to Spir-V conversion:");
            AGS_ERROR("{}", glslang_shader_get_info_log(shader));
            AGS_ERROR("{}", glslang_shader_get_info_debug_log(shader));
            glslang_shader_delete(shader);
            return;
        }

        glslang_program_t* program = glslang_program_create();
        glslang_program_add_shader(program, shader);

        if (!glslang_program_link(program, GLSLANG_MSG_SPV_RULES_BIT | GLSLANG_MSG_VULKAN_RULES_BIT)) {
            AGS_ERROR("Error in GLSL to Spir-V conversion:");
            AGS_ERROR("{}", glslang_program_get_info_log(program));
            AGS_ERROR("{}", glslang_program_get_info_debug_log(program));
            glslang_program_delete(program);
            glslang_shader_delete(shader);
            return;
        }

        glslang_program_SPIRV_generate(program, GLSLANG_STAGE_VERTEX);

        std::vector<unsigned> spirv_bytecode;
        spirv_bytecode.resize(glslang_program_SPIRV_get_size(program));
        glslang_program_SPIRV_get(program, spirv_bytecode.data());

        const char* spirv_messages = glslang_program_SPIRV_get_messages(program);
        if (spirv_messages) {
            AGS_ERROR("Error in GLSL to Spir-V conversion:");
            AGS_ERROR("{}", spirv_messages);
        }

        glslang_program_delete(program);
        glslang_shader_delete(shader);

        load_spirv({spirv_bytecode.data(), spirv_bytecode.size()});
    }

    void Vertex_shader::load_spirv(aul::Span<const std::uint32_t> bytecode) {
        #ifdef AGS_ARE_VK10_DEBUG
        retrieve_module_metadata(bytecode.data(), bytecode.size());
        #endif

        vk::ShaderModuleCreateInfo module_create_info{
            vk::ShaderModuleCreateFlagBits{},
            bytecode.size() * sizeof(std::uint32_t),
            bytecode.data()
        };

        shader_module = Device_kernel::get_graphics_device().handle.createShaderModule(module_create_info);
    }

    #if defined(AGS_ARE_VK10_DEBUG)
    void Vertex_shader::retrieve_module_metadata(const void* data, std::size_t n) {
        SpvReflectShaderModule reflection_module;
        SpvReflectResult result = spvReflectCreateShaderModule(
            n,
            data,
            &reflection_module
        );

        std::uint32_t variable_count;
        result = spvReflectEnumerateInputVariables(&reflection_module, &variable_count, nullptr);

        std::vector<SpvReflectInterfaceVariable*> input_variables{};
        result = spvReflectEnumerateInputVariables(&reflection_module, &variable_count, input_variables.data());

        spvReflectDestroyShaderModule(&reflection_module);
    }
    #endif

    void Vertex_shader::unload() {
        if (!shader_module) {
            return;
        }

        auto& graphics_device = Device_kernel::get_graphics_device().handle;
        graphics_device.destroyShaderModule(shader_module);
        shader_module = VK_NULL_HANDLE;

        #if defined(AGS_ARE_VK10_DEBUG)
        spvReflectDestroyShaderModule(reflect_data.get());
        #endif
    }

    Vertex_shader::operator bool() const noexcept {
        return static_cast<bool>(shader_module);
    }

    //=========================================================================
    // Fragment Shader Object
    //=========================================================================

    Fragment_shader::Fragment_shader():
        shader_module(VK_NULL_HANDLE) {}

    Fragment_shader::~Fragment_shader() {
        unload();
    }

    void Fragment_shader::load_glsl(std::string_view source) {
        //TODO: Populate resource according to hardware capabilities
        glslang_limits_t limits{
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true
        };

        glslang_resource_t resource{
            32,
            6,
            32,
            32,
            64,
            4096,
            64,
            32,
            80,
            32,
            4096,
            32,
            128,
            8,
            16,
            16,
            15,
            -8,
            7,
            8,
            65535,
            65535,
            65535,
            1024,
            1024,
            64,
            1024,
            16,
            8,
            8,
            1,
            60,
            64,
            64,
            128,
            128,
            8,
            8,
            8,
            0,
            0,
            0,
            0,
            0,
            8,
            8,
            16,
            256,
            1024,
            1024,
            64,
            128,
            128,
            16,
            1024,
            4096,
            128,
            128,
            16,
            1024,
            120,
            32,
            64,
            16,
            0,
            0,
            0,
            0,
            8,
            8,
            1,
            0,
            0,
            0,
            0,
            1,
            1,
            16384,
            4,
            64,
            8,
            8,
            4,
            256,
            512,
            32,
            1,
            1,
            32,
            1,
            1,
            4,
            256,
            256,
            128,
            128,
            128,
            128,
            128,
            128,
            4,
            1,
            limits
        };

        const glslang_input_t input {
            GLSLANG_SOURCE_GLSL,
            GLSLANG_STAGE_FRAGMENT,
            GLSLANG_CLIENT_VULKAN,
            GLSLANG_TARGET_VULKAN_1_0,
            GLSLANG_TARGET_SPV,
            GLSLANG_TARGET_SPV_1_0,
            source.data(),
            100,
            GLSLANG_CORE_PROFILE,
            false,
            false,
            GLSLANG_MSG_DEFAULT_BIT,
            &resource
        };

        glslang_shader_t* shader = glslang_shader_create(&input);

        if (!glslang_shader_preprocess(shader, &input)) {
            AGS_ERROR("Error in GLSL to SpirV conversion:");
            AGS_ERROR("{}", glslang_shader_get_info_log(shader));
            AGS_ERROR("{}", glslang_shader_get_info_debug_log(shader));
            glslang_shader_delete(shader);
            return;
        }

        if (!glslang_shader_parse(shader, &input)) {
            AGS_ERROR("Error in GLSL to SpirV conversion:");
            AGS_ERROR("{}", glslang_shader_get_info_log(shader));
            AGS_ERROR("{}", glslang_shader_get_info_debug_log(shader));
            glslang_shader_delete(shader);
            return;
        }

        glslang_program_t* program = glslang_program_create();
        glslang_program_add_shader(program, shader);

        if (!glslang_program_link(program, GLSLANG_MSG_SPV_RULES_BIT | GLSLANG_MSG_VULKAN_RULES_BIT)) {
            AGS_ERROR("Error in GLSL to SpirV conversion:");
            AGS_ERROR("{}", glslang_program_get_info_log(program));
            AGS_ERROR("{}", glslang_program_get_info_debug_log(program));
            glslang_program_delete(program);
            glslang_shader_delete(shader);
            return;
        }

        glslang_program_SPIRV_generate(program, GLSLANG_STAGE_FRAGMENT);

        std::vector<unsigned> spirv_bytecode;
        spirv_bytecode.resize(glslang_program_SPIRV_get_size(program));
        glslang_program_SPIRV_get(program, spirv_bytecode.data());

        const char* spirv_messages = glslang_program_SPIRV_get_messages(program);
        if (spirv_messages) {
            AGS_ERROR("Error in GLSL to SpirV conversion:");
            AGS_ERROR("{}", spirv_messages);
        }

        glslang_program_delete(program);
        glslang_shader_delete(shader);

        load_spirv({spirv_bytecode.data(), spirv_bytecode.size()});
    }

    void Fragment_shader::load_spirv(aul::Span<const std::uint32_t> bytecode) {
        #ifdef AGS_ARE_VK10_DEBUG
        retrieve_module_metadata(bytecode.data(), bytecode.size());
        #endif

        vk::ShaderModuleCreateInfo module_create_info{
            vk::ShaderModuleCreateFlagBits{},
            bytecode.size() * sizeof(std::uint32_t),
            bytecode.data()
        };

        shader_module = Device_kernel::get_graphics_device().handle.createShaderModule(module_create_info);
    }

    #if defined(AGS_ARE_VK10_DEBUG)
    void Fragment_shader::retrieve_module_metadata(const void* data, std::size_t n) {
        SpvReflectShaderModule reflection_module;
        SpvReflectResult result = spvReflectCreateShaderModule(
            n,
            data,
            &reflection_module
        );

        std::uint32_t variable_count;
        result = spvReflectEnumerateInputVariables(&reflection_module, &variable_count, nullptr);

        std::vector<SpvReflectInterfaceVariable*> input_variables{};
        result = spvReflectEnumerateInputVariables(&reflection_module, &variable_count, input_variables.data());

        spvReflectDestroyShaderModule(&reflection_module);
    }
    #endif

    void Fragment_shader::unload() {
        if (!shader_module) {
            return;
        }

        auto& graphics_device = Device_kernel::get_graphics_device().handle;
        graphics_device.destroyShaderModule(shader_module);
        shader_module = VK_NULL_HANDLE;

        #if defined(AGS_ARE_VK10_DEBUG)
        spvReflectDestroyShaderModule(reflect_data.get());
        #endif
    }

    Fragment_shader::operator bool() const noexcept {
        return static_cast<bool>(shader_module);
    }

    //=========================================================================
    // Shader program object
    //=========================================================================

    //=====================================================
    // -ctors
    //=====================================================

    //Shader::Shader(Shader&& shader) noexcept;

    Shader_program::~Shader_program() {
        auto& device = Device_kernel::get_graphics_device().handle;
        device.destroy(pipeline);
        device.destroy(pipeline_layout);
    }

    //=====================================================
    // Assignment operators
    //=====================================================

    //Shader_program& Shader_program::operator=(Shader_program&& rhs) noexcept {}

    //=====================================================
    // Resource mutators
    //=====================================================

    /*
    void Shader_program::load(const std::string& vert_src, const std::string& frag_src) {
        shaderc::Compiler compiler{};
        auto vertc_output = compiler.CompileGlslToSpv(
            vert_src,
            shaderc_shader_kind::shaderc_glsl_vertex_shader,
            "Vertex source", //TODO: Replace with something more descriptive
            Shader_kernel::options
        );

        if (vertc_output.GetCompilationStatus() != shaderc_compilation_status::shaderc_compilation_status_success) {
            throw std::runtime_error("Failed to compile vertex shader: " + vertc_output.GetErrorMessage());
        }

        auto fragc_output = compiler.CompileGlslToSpv(
            frag_src,
            shaderc_shader_kind::shaderc_glsl_fragment_shader,
            "Fragment source", //TODO: Replace with something more descriptive
            Shader_kernel::options
        );

        if (fragc_output.GetCompilationStatus() != shaderc_compilation_status::shaderc_compilation_status_success) {
            throw std::runtime_error("Failed to compile fragment shader: " + vertc_output.GetErrorMessage());
        }

        //TODO: Check the correctness of the subtraction being done here. The
        // pointers are to 32-bit integers instead of individual bytes so the
        // arithmetic might be off by a factor of four
        load(
            vertc_output.begin(),
            (vertc_output.end() - vertc_output.begin()),
            fragc_output.begin(),
            (fragc_output.end() - fragc_output.begin())
        );
    }
    */

    void Shader_program::compose(const Framebuffer& framebuffer, const Vertex_shader& vs, const Fragment_shader& fs) {
        #if defined(AGS_ARE_VK10_DEBUG)
        if (!vs.module) {
            throw std::runtime_error("Vertex shader object did not hold a resource");
        }

        if (!fs.module) {
            throw std::runtime_error("Fragment shader object did not hold a resource");
        }
        #endif

        auto& graphics_device = Device_kernel::get_graphics_device().handle;

        vk::PipelineShaderStageCreateInfo stage_create_infos[2] {
            vk::PipelineShaderStageCreateInfo{
                vk::PipelineShaderStageCreateFlags{},
                vk::ShaderStageFlagBits::eVertex,
                vs.shader_module,
                "main",
                nullptr
            },
            vk::PipelineShaderStageCreateInfo{
                vk::PipelineShaderStageCreateFlags{},
                vk::ShaderStageFlagBits::eFragment,
                fs.shader_module,
                "main",
                nullptr
            }
        };

        // TODO: Create appropriate dummy render pass
        // Identify outputs of fragment shader and create render pass that has
        // capabilities of the

        vk::PipelineDepthStencilStateCreateInfo depth_stencil_create_info{
            vk::PipelineDepthStencilStateCreateFlags{},
            true,
            true,
            vk::CompareOp::eLess,
            false,
            false,
            vk::StencilOpState{},
            vk::StencilOpState{},
            0.0f,
            1.0f
        };

        vk::PipelineDepthStencilStateCreateInfo* depth_stencil_create_pointer = nullptr;
        if (framebuffer.depth_attachment_format() != Depth_format::NULL_DEPTH_FORMAT) {
            depth_stencil_create_pointer = &depth_stencil_create_info;
        }

        vk::PipelineLayoutCreateInfo pipeline_layout_create_info{
            vk::PipelineLayoutCreateFlags{},
            {}, //TODO: Specify descriptors
            {}, //TODO: Specify push constants
        };

        pipeline_layout = graphics_device.createPipelineLayout(pipeline_layout_create_info);

        auto multisample_create_info = Shader_kernel::generate_multisample_create_info(framebuffer.samples());

        vk::GraphicsPipelineCreateInfo pipeline_create_info{
            vk::PipelineCreateFlags{},
            2,
            stage_create_infos,
            &Shader_kernel::default_pipeline_vertex_input_state_create_info,
            &Shader_kernel::triangle_list_assembly_state_create_info,
            nullptr,
            &Shader_kernel::default_pipeline_viewport_state_create_info,
            &Shader_kernel::default_pipeline_rasterization_state_create_info,
            &multisample_create_info,
            depth_stencil_create_pointer,
            &Shader_kernel::default_color_blend_state_create_info,
            &Shader_kernel::dynamic_state_create_info,
            pipeline_layout ,
            framebuffer.render_pass,
            0 //Subpass
        };

        vk::Result result{};
        std::tie(result, pipeline) = graphics_device.createGraphicsPipeline(
            VK_NULL_HANDLE,
            pipeline_create_info
        );

        if (result != vk::Result::eSuccess) {
            //TODO: Replace with return and log error
            throw std::runtime_error("Failed to create graphics pipeline.");
        }
    }

    void Shader_program::unload() {
        //TODO: Implement
    }

    vk::Pipeline Shader_program::native_handle() const {
        return pipeline;
    }

    Shader_program::operator bool() const {
        return pipeline;
    }

}
