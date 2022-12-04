/**
 * @ Author: Roxana Stancu (esettes)
 * @ Created: 22/12/04 01:38
 * @ Modified: 22/12/04 02:32
 * @ Description:
 */

#include "device.h"
#include "pipeline.h"
#include <stdio.h>
#include <string.h>

VkPipeline g_pipeline = VK_NULL_HANDLE;

#if 0
void	create_pipeline(void)
{
	VkComputePipelineCreateInfo pipeline_info;

	pipeline_info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
	pipeline_info.stage = g_compute_stage;
	pipeline_info.layout = g_pipeline_layout;
	pipeline_info.basePipelineHandle = -1;
	if (vkCreateComputePipelines(g_logical_device, VK_NULL_HANDLE, 1,
		&create_pipeline, NULL, &g_pipeline) != VK_SUCCESS)
	{
		printf("[ERROR] Pipeline creation failure.\n");
		return ;
	}
}
#endif