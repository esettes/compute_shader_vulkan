/**
 * @ Author: Roxana Stancu (esettes)
 * @ Created: 2022/12/04 01:38
 * @ Modified: 2022/12/09 04:25
 * 
 * @ Description: Defining process of shader execution. Create pipeline; shader
 * and layout handles
 * 
 * Allocated data buffers must be bound to a descriptor set and
 * the ds must be bound to the command buffer. This way Vulkan
 * can give the memory to the shader.
 */

#include "device.h"
#include "pipeline.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

VkPipeline				g_pipeline = VK_NULL_HANDLE;
VkShaderModule			g_shader_module = VK_NULL_HANDLE;
VkPipelineLayout		g_pipeline_layout = VK_NULL_HANDLE;
VkDescriptorSetLayout	g_descriptor_set_layout = VK_NULL_HANDLE;

static size_t	get_file_size(FILE *f)
{
	size_t	size;
	size_t	curr_pos = ftell(f);
	
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, curr_pos, SEEK_SET);
	return (size);
}

void	create_compute_shader(void)
{
	FILE	*f = fopen("./src/shader/bin/shader.spv","rb");

	if(!f)
	{
		printf("[Error] Can't open shader file.\n");
		return ;
	}
	size_t size = get_file_size(f);
	const uint32_t *shader_data = (const uint32_t *)calloc(size + 1, 1);

	if (!shader_data)
	{
		printf("[Error] Out of memory when reading shader bin.\n");
		fclose(f);
		f = NULL;
		return ;
	}
	fread((void *)shader_data, 1, size, f);
	fclose(f);
	f = NULL;
	
	/* Put the binary data to structure */
	VkShaderModuleCreateInfo	create_info;
	
	memset(&create_info, 0, sizeof(create_info));
	create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	create_info.codeSize = size;
	create_info.pCode = (uint32_t *)shader_data;
	if (vkCreateShaderModule(g_logical_device, &create_info, NULL, &g_shader_module)
		!= VK_SUCCESS)
	{
		printf("[Error] Can't create shader module.\n");
		return ;
	}
}
/**
 * Specifies the types of buffers used by the shader/s.
 * Descriptor shoud be bound to the shader and it was configurated with 
 * the number of bindings in the shader.
 */
void	create_descriptor_set_layout(void)
{
	VkDescriptorSetLayoutBinding	layout_bindings[2];
	VkDescriptorSetLayoutCreateInfo	create_info;

	memset(&layout_bindings, 0, sizeof(layout_bindings));
	layout_bindings[0].binding = 0;
	layout_bindings[0].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
	layout_bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
	layout_bindings[0].descriptorCount = 1;
	layout_bindings[1].binding = 1;
	layout_bindings[1].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
	layout_bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
	layout_bindings[1].descriptorCount = 1;
	memset(&create_info, 0, sizeof(create_info));
	create_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	create_info.bindingCount = 2;
	create_info.pBindings = layout_bindings;
	if (vkCreateDescriptorSetLayout(g_logical_device, &create_info, NULL,
		&g_descriptor_set_layout) != VK_SUCCESS)
	{
		printf("[Error] Can't create descriptor set layout.\n");
		return ;
	}
}
/**
 * Defines an interface between shader and data memory it uses. Sets
 * info about descriptor set layout and other, and stores it in global var
 * g_pipeline_layout.
 */
void	create_pipeline_layout(void)
{
	create_descriptor_set_layout();
	VkPipelineLayoutCreateInfo	layout_info;

	memset(&layout_info, 0, sizeof(layout_info));
	layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	/* Define x, y, z buffer of glsl */
	layout_info.pSetLayouts = &g_descriptor_set_layout;
	layout_info.setLayoutCount = 1;
	if (vkCreatePipelineLayout(g_logical_device, &layout_info, NULL,
		&g_pipeline_layout) != VK_SUCCESS)
	{
		printf("[Error] Can't create pipeline layout.\n");
		return ;
	}
}

void	create_pipeline(void)
{
	create_pipeline_layout();
	create_compute_shader();
	VkComputePipelineCreateInfo pipeline_info;

	memset(&pipeline_info, 0, sizeof(pipeline_info));
	pipeline_info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
	pipeline_info.layout = g_pipeline_layout;
	pipeline_info.basePipelineIndex = -1;
	pipeline_info.stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	pipeline_info.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
	pipeline_info.stage.pName = "main";
	pipeline_info.stage.module = g_shader_module;
	if (pipeline_info.stage.module == VK_NULL_HANDLE)
	{
		printf("[Error] Pipeline stage module is NULL.\n");
		return ;
	}
	if (vkCreateComputePipelines(g_logical_device, VK_NULL_HANDLE, 1,
		&pipeline_info, NULL, &g_pipeline) != VK_SUCCESS)
	{
		printf("[ERROR] Pipeline creation failure.\n");
		return ;
	}
}
/**
 * Destroys the pipeline,descriptor set layout and pipeline layout.
 */
void	destroy_pipeline(void)
{
	if (g_pipeline_layout != VK_NULL_HANDLE)
	{
		vkDestroyPipelineLayout(g_logical_device, g_pipeline_layout, NULL);
	}
	if (g_descriptor_set_layout != VK_NULL_HANDLE)
	{
		vkDestroyDescriptorSetLayout(g_logical_device, g_descriptor_set_layout, NULL);
	}
	if (g_pipeline != VK_NULL_HANDLE)
	{
		vkDestroyPipeline(g_logical_device, g_pipeline, NULL);
	}
}

void	destroy_shader_module(void)
{
	if (g_shader_module != VK_NULL_HANDLE)
	{
		vkDestroyShaderModule(g_logical_device, g_shader_module, NULL);
	}
}