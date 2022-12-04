/**
 * @ Author: Roxana Stancu (esettes)
 * @ Created: 22/12/02 23:41
 * @ Modified: 22/12/03 23:07
 * 
 * @ Description: commandPool means where to allocate the command buffer, 
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

VkCommandBuffer g_command_buffer = VK_NULL_HANDLE;

void	set_command_buffer(void)
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
		printf("Command buffer allocation failed\n");
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
	vkCmdDispatch(g_command_buffer, 1, 1, 1);
	/**
	 * End recording
	 */
	if (vkEndCommandBuffer(g_command_buffer) != VK_SUCCESS)
	{
		printf("Buffer ending failed\n");
		return ;
	}
}

int	compute(void)
{
	VkSubmitInfo submit_info;

	memset(&submit_info, 0, sizeof(submit_info));
	submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	/**
	 * Array of command buffers handles
	 */
	submit_info.pCommandBuffers = &g_command_buffer;
	if (vkQueueSubmit(g_compute_queue, 1, &submit_info, NULL) != VK_SUCCESS)
	{
		printf("Command buffer submission failed\n");
		return (-1);
		#if TEMP_DISABLED
		#endif
	}
	

	return (0);
}