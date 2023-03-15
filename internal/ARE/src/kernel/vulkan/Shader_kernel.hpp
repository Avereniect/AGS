#ifndef AGS_ARE_VK_SHADER_KERNEL_HPP
#define AGS_ARE_VK_SHADER_KERNEL_HPP

#include <ags/Graphics_includes.hpp>

#include <glslang/Public/ShaderLang.h>

#include "Enums.hpp"

namespace ags::are::vk_kernel {

    class Shader;
    class Vertex_shader;
    class Fragment_shader;
    class Shader_program;

    class Shader_kernel {
    public:

        friend class Shader;
        friend class Vertex_shader;
        friend class Fragment_shader;
        friend class Shader_program;

        //=================================================
        // State methods
        //=================================================

        static void init();
        static void term();

        //=================================================
        // Utility Functions
        //=================================================

        static vk::PipelineMultisampleStateCreateInfo generate_multisample_create_info(Sample_count s);

    private:

        //=================================================
        // Static members
        //=================================================

        //static thread_local shaderc::Compiler compiler;
        //static shaderc::CompileOptions options;



        static const vk::PipelineVertexInputStateCreateInfo default_pipeline_vertex_input_state_create_info;

        static const vk::PipelineInputAssemblyStateCreateInfo triangle_list_assembly_state_create_info;
        static const vk::PipelineInputAssemblyStateCreateInfo triangle_strip_assembly_state_create_info;

        static const std::array<vk::DynamicState, 1> default_dynamic_states;
        static const vk::PipelineDynamicStateCreateInfo dynamic_state_create_info;

        static const vk::Viewport default_viewport;
        static const vk::Rect2D default_scissor;
        static const vk::PipelineViewportStateCreateInfo default_pipeline_viewport_state_create_info;

        static const vk::PipelineRasterizationStateCreateInfo default_pipeline_rasterization_state_create_info;

        static const vk::PipelineMultisampleStateCreateInfo default_pipeline_multisample_state_create_info;

        static const vk::ColorComponentFlags rgba_color_component_flags;
        static const vk::PipelineColorBlendAttachmentState default_pipeline_color_blend_attachment_state;
        static const vk::PipelineColorBlendStateCreateInfo default_color_blend_state_create_info;

        //=================================================
        // Helper functions
        //=================================================

        //static shaderc::CompileOptions create_options();

    };

}

#endif //AGS_ARE_VK_SHADER_KERNEL_HPP
