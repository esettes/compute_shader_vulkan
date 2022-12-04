/**
 * @ Author: Roxana Stancu (esettes)
 * @ Created: 2022/12/04 01:38
 * @ Modified: 2022/12/04 16:32
 */

#include <vulkan/vulkan.h>

# ifndef PIPELINE_H
# define PIPELINE_H

extern VkPipeline				g_pipeline;
extern VkPipelineLayout			g_pipeline_layout;
extern VkDescriptorSetLayout	descriptor_set_layout;

void	create_pipeline(void);
void	destroy_pipeline(void);

# endif