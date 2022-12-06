/**
 * @ Author: Roxana Stancu (esettes)
 * @ Created: 2022/12/02 23:41
 * @ Modified: 2022/12/06 14:21
 * 
 * @ Description: Alloc command buffer in command pool and submit queue. Create
 * descriptor set for buffers.
 * 
 * commandPool means where to allocate the command buffer, 
 * which aren't allocated individually.
 * 
 * VkCommandBufferBeginInfo records operations that want to be executed.
 * 
 * static var command_buff_begin_info means that commandBuffer is intented
 * to be used once and reset afterwards.
 * 
 * Now with vkCmdDispatch can record various operations to the command buffer 
 * and run shader in many parallel runs,
 * can set how many groups of shader groups should be start.
 * Each run has its own index, which also helps to find which part of the data
 * belongs to the particular run.
 * vkCmdDispatch has 3 dimensions, which determinate how many groups in each
 * dimension should run. Each dimension(x y z) indicates number of indexes, 
 * and therese values multiplied results in the number of groups that will run.
 */

#include "compute.h"
#include <string.h>
#include <stdio.h>

VkCommandBuffer	g_command_buffer = VK_NULL_HANDLE;
VkDescriptorSet	g_descriptor_set = VK_NULL_HANDLE;
/**
 * Alloc command buffer and record dispatch.
 */
void	create_command_buffer(void)
{
	VkCommandBufferAllocateInfo alloc_info;

	memset(&alloc_info, 0, sizeof(alloc_info));
	alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	alloc_info.commandPool = g_compute_command_pool;
	alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	alloc_info.commandBufferCount = 1;
	if (vkAllocateCommandBuffers(g_logical_device, &alloc_info, &g_command_buffer)
		!= VK_SUCCESS)
	{
		printf("[ERROR] Command buffer allocation failed\n");
		return ;
	}
	/**
	 * Record operations that want to be executed
	 */
	VkCommandBufferBeginInfo begin_info;
	
	memset(&begin_info, 0, sizeof(begin_info));
	begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	if (vkBeginCommandBuffer(g_command_buffer, &begin_info) != VK_SUCCESS)
	{
		printf("Buffer begining failed\n");
		return ;
	}
	vkCmdBindPipeline(g_command_buffer, VK_PIPELINE_BIND_POINT_COMPUTE,
		g_pipeline);
	/* This func expects an array of descriptor sets, it should be the index of
	the first. */
	vkCmdBindDescriptorSets(g_command_buffer, VK_PIPELINE_BIND_POINT_COMPUTE,
		g_pipeline_layout, 0, 1, &g_descriptor_set, 0, NULL);
	vkCmdDispatch(g_command_buffer, 1, 1, 1);
	/* End recording */
	if (vkEndCommandBuffer(g_command_buffer) != VK_SUCCESS)
	{
		printf("[ERROR] Buffer ending failed\n");
		return ;
	}
}

/**
 * Submits command buffer to queue.
 * 
 * @return 0 if success, else failed.
 */
int	compute(void)
{
	VkFence				fence;
	VkFenceCreateInfo	fence_info;
	VkSubmitInfo		submit_info;

	memset(&fence_info, 0, sizeof(fence_info));
	fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	if (vkCreateFence(g_logical_device, &fence_info, NULL, &fence) != VK_SUCCESS)
	{
		printf("[ERROR] Can't create fence.\n");
		//return (0);
		return (-1);
	}
	memset(&submit_info, 0, sizeof(submit_info));
	submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	/* Array of command buffers handles. Sync tool with fence. */
	submit_info.pCommandBuffers = &g_command_buffer;
	if (vkQueueSubmit(g_compute_queue, 1, &submit_info, fence) != VK_SUCCESS)
	{
		printf("[ERROR] Command buffer submission failed\n");
		return (-1);
		#if TEMP_DISABLED
		#endif
	}
	if (vkWaitForFences(g_logical_device, 1, &fence, VK_TRUE, UINT64_MAX) != VK_SUCCESS)
	{
		printf("[ERROR] Waiting for fence failed.\n");
	}
	else
	{
		printf("[INFO] Waiting for fence success.\n");
	}
	vkDestroyFence(g_logical_device, fence, NULL);
	return (0);
}

void	create_descriptor_set(void)
{
	create_descriptor_pool();
	VkDescriptorSetAllocateInfo alloc_info;

	memset(&alloc_info, 0, sizeof(alloc_info));
	alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	/* Number of descriptor set layouts. */
	alloc_info.descriptorSetCount = 1;
	alloc_info.pSetLayouts = &g_descriptor_set_layout;
	alloc_info.descriptorPool = g_descriptor_pool;
	if (vkAllocateDescriptorSets(g_logical_device, &alloc_info,
		&g_descriptor_set) != VK_SUCCESS)
	{
		printf("[ERROR] Can't allocate descriptor set.\n");
	}
}
