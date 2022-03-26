//
// Created by avereniect on 3/14/22.
//
#include "Shader_kernel.hpp"

namespace ags::are::vk10 {

    //=====================================================
    // Static members
    //=====================================================

    thread_local shaderc::Compiler Shader_kernel::compiler{};

    shaderc::CompileOptions Shader_kernel::options{create_options()};

    const vk::PipelineVertexInputStateCreateInfo Shader_kernel::default_pipeline_vertex_input_state_create_info{
        vk::PipelineVertexInputStateCreateFlags{},
        0,
        nullptr,
        0,
        nullptr
    };

    const vk::PipelineInputAssemblyStateCreateInfo Shader_kernel::triangle_list_assembly_state_create_info{
        vk::PipelineInputAssemblyStateCreateFlagBits{},
        vk::PrimitiveTopology::eTriangleList,
        false
    };

    const vk::PipelineInputAssemblyStateCreateInfo Shader_kernel::triangle_strip_assembly_state_create_info{
        vk::PipelineInputAssemblyStateCreateFlagBits{},
        vk::PrimitiveTopology::eTriangleStrip,
        false
    };

    const std::array<vk::DynamicState, 1> Shader_kernel::default_dynamic_states{
        vk::DynamicState::eViewport
    };

    const vk::PipelineDynamicStateCreateInfo Shader_kernel::dynamic_state_create_info{
        vk::PipelineDynamicStateCreateFlags{},
        Shader_kernel::default_dynamic_states.size(),
        Shader_kernel::default_dynamic_states.data()
    };

    const vk::Viewport Shader_kernel::default_viewport{
        0.0f,
        0.0f,
        static_cast<float>(800), //This is marked as dynamic state so the
        static_cast<float>(600), //actual values here don't matter
        0.0f,
        1.0f
    };

    const vk::Rect2D Shader_kernel::default_scissor{
        {0, 0},
        {800, 600}
    };

    const vk::PipelineViewportStateCreateInfo Shader_kernel::default_pipeline_viewport_state_create_info{
        vk::PipelineViewportStateCreateFlags{},
        1,
        &Shader_kernel::default_viewport,
        1,
        &Shader_kernel::default_scissor
    };

    const vk::PipelineRasterizationStateCreateInfo Shader_kernel::default_pipeline_rasterization_state_create_info{
        vk::PipelineRasterizationStateCreateFlags{},
        false,
        false,
        vk::PolygonMode::eFill,
        vk::CullModeFlagBits::eNone,
        vk::FrontFace::eCounterClockwise,
        false,
        0.0f,
        0.0f,
        0.0f,
        1.0f
    };

    const vk::PipelineMultisampleStateCreateInfo Shader_kernel::default_pipeline_multisample_state_create_info{
        vk::PipelineMultisampleStateCreateFlags{},
        vk::SampleCountFlagBits::e1,
        false,
        1.0f,
        nullptr,
        false,
        false
    };

    const vk::ColorComponentFlags Shader_kernel::rgba_color_component_flags{
        vk::ColorComponentFlagBits::eR |
        vk::ColorComponentFlagBits::eG |
        vk::ColorComponentFlagBits::eB |
        vk::ColorComponentFlagBits::eA
    };

    const vk::PipelineColorBlendAttachmentState Shader_kernel::default_pipeline_color_blend_attachment_state{
        false,
        vk::BlendFactor::eOne,
        vk::BlendFactor::eZero,
        vk::BlendOp::eAdd,
        vk::BlendFactor::eOne,
        vk::BlendFactor::eZero,
        vk::BlendOp::eAdd,
        rgba_color_component_flags
    };

    const vk::PipelineColorBlendStateCreateInfo Shader_kernel::default_color_blend_state_create_info{
        vk::PipelineColorBlendStateCreateFlags{},
        false,
        vk::LogicOp::eCopy,
        1,
        &default_pipeline_color_blend_attachment_state,
        {
            0.0f, 0.0f, 0.0f, 0.0f
        }
    };

    //=====================================================
    // State methods
    //=====================================================

    void Shader_kernel::init() {

    }

    void Shader_kernel::term() {

    }

    //=====================================================
    // Helper functions
    //=====================================================

    shaderc::CompileOptions Shader_kernel::create_options() {
        shaderc::CompileOptions ret;

        #if defined(AGS_ARE_DEBUG)
        ret.SetOptimizationLevel(shaderc_optimization_level_zero);
        #else
        ret.SetOptimizationLevel(shaderc_optimization_level_performance);
        #endif

        ret.SetTargetSpirv(shaderc_spirv_version_1_0);

        return ret;
    }

}
