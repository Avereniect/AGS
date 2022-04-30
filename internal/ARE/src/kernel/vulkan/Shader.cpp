//
// Created by avereniect on 1/21/22.
//
#include "Shader.hpp"
#include "Shader_kernel.hpp"
#include "Kernel.hpp"

#include <shaderc/shaderc.hpp>
#include <spirv-reflect/spirv_reflect.h>

#include <stdexcept>

namespace ags::are::vk10 {

    //=========================================================================
    // Vertex Shader Object
    //=========================================================================

    Vertex_shader::Vertex_shader():
        module(VK_NULL_HANDLE) {}

    Vertex_shader::Vertex_shader(Vertex_shader&& vs) noexcept:
        module(std::exchange(vs.module, VK_NULL_HANDLE)) {}

    Vertex_shader::~Vertex_shader() {
        Device_kernel::get_graphics_device().handle.destroyShaderModule(module);

        #if defined(AGS_ARE_VK10_DEBUG)
        spvReflectDestroyShaderModule(reflect_data.get());
        #endif
    }

    Vertex_shader& Vertex_shader::operator=(Vertex_shader&& rhs) noexcept {
        module = std::exchange(rhs.module, VK_NULL_HANDLE);
        return *this;
    }

    void Vertex_shader::load_source(const std::string_view source) {
        auto compilation_output = Shader_kernel::compiler.CompileGlslToSpv(
            source.data(),
            (source.end() - source.begin()),
            shaderc_shader_kind::shaderc_glsl_vertex_shader,
            "Vertex source",
            "name",
            Shader_kernel::options
        );

        load_bytecode({compilation_output.begin(), compilation_output.end()});
    }

    void Vertex_shader::load_bytecode(aul::Span<const std::uint32_t> bytecode) {
        #ifdef AGS_ARE_VK10_DEBUG
        retrieve_module_metadata(bytecode.data(), bytecode.size());
        #endif

        vk::ShaderModuleCreateInfo module_create_info{
            vk::ShaderModuleCreateFlagBits{},
            bytecode.size() * sizeof(std::uint32_t),
            bytecode.data()
        };

        module = Device_kernel::get_graphics_device().handle.createShaderModule(module_create_info);
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
        if (!module) {
            return;
        }

        auto& graphics_device = Device_kernel::get_graphics_device().handle;
        graphics_device.destroyShaderModule(module);
        module = VK_NULL_HANDLE;
    }

    Vertex_shader::operator bool() const noexcept {
        return static_cast<bool>(module);
    }

    //=========================================================================
    // Fragment Shader Object
    //=========================================================================

    Fragment_shader::Fragment_shader():
        module(VK_NULL_HANDLE) {}

    //=========================================================================
    // Shader program object
    //=========================================================================

    //=====================================================
    // -ctors
    //=====================================================

    //Shader::Shader(Shader&& shader) noexcept;

    Shader_program::~Shader_program() {

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
                vs.module,
                "main",
                nullptr
            },
            vk::PipelineShaderStageCreateInfo{
                vk::PipelineShaderStageCreateFlags{},
                vk::ShaderStageFlagBits::eFragment,
                fs.module,
                "main",
                nullptr
            }
        };

        // TODO: Create appropriate dummy render pass
        // Identify outputs of fragment shader and create render pass that has
        // capabilities of the

        vk::GraphicsPipelineCreateInfo pipeline_create_info{
            vk::PipelineCreateFlags{},
            2,
            stage_create_infos,
            &Shader_kernel::default_pipeline_vertex_input_state_create_info,
            &Shader_kernel::triangle_list_assembly_state_create_info,
            nullptr,
            &Shader_kernel::default_pipeline_viewport_state_create_info,
            &Shader_kernel::default_pipeline_rasterization_state_create_info,
            &Shader_kernel::default_pipeline_multisample_state_create_info,
            nullptr,
            &Shader_kernel::default_color_blend_state_create_info,
            &Shader_kernel::dynamic_state_create_info,
            vk::PipelineLayout{},
            framebuffer.render_pass,
            0 //Subpass
        };

        #if defined(AGS_ARE_VK10_DEBUG)
        vk::Result result{};
        std::tie(result, pipeline) = graphics_device.createGraphicsPipeline(VK_NULL_HANDLE, pipeline_create_info);
        if (result != vk::Result::eSuccess) {
            throw std::runtime_error("Failed to create graphics pipeline.");
        }
        #endif
    }

    //void Shader::unload();

    Shader_program::operator bool() const {
        return pipeline;
    }

    Shader_program::operator vk::Pipeline() const {
        return pipeline;
    }

}
