/**
 * @ Author: Roxana Stancu (esettes)
 * @ Created: 2022/12/04 01:38
 * @ Modified: 2022/12/04 18:01
 */

#include <vulkan/vulkan.h>

# ifndef PIPELINE_H
# define PIPELINE_H

extern VkPipeline				g_pipeline;
extern VkPipelineLayout			g_pipeline_layout;
extern VkDescriptorSetLayout	g_descriptor_set_layout;

void	create_pipeline(void);
void	destroy_pipeline(void);

# endif