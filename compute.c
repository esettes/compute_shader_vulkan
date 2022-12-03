/**
 * @ Author: Roxana Stancu (esettes)
 * @ Created: 22/12/02 23:41
 * @ Modified: 22/12/03 15:25
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

VkCommandBuffer g_commandBuffer = VK_NULL_HANDLE;

void	set_command_buffer(void)
{
	VkCommandBufferAllocateInfo allocInfo;

	memset(&allocInfo, 0, sizeof(allocInfo));
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;
	if (vkAllocateCommandBuffers(logicDevice, &allocInfo, &g_commandBuffer)
		!= VK_SUCCESS)
	{
		printf("Command buffer allocation failed\n");
		return ;
	}
	/**
	 * Record operations that want to be executed
	 */
	VkCommandBufferBeginInfo beginInfo;
	memset(&beginInfo, 0, sizeof(beginInfo));
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	if (vkBeginCommandBuffer(g_commandBuffer, &beginInfo) != VK_SUCCESS)
	{
		printf("Buffer begining failed\n");
		return ;
	}
	vkCmdDispatch(g_commandBuffer, 1, 1, 1);
	/**
	 * End recording
	 */
	if (vkEndCommandBuffer(g_commandBuffer) != VK_SUCCESS)
	{
		printf("Buffer ending failed\n");
		return ;
	}
}

int	compute(void)
{
	VkSubmitInfo submitInfo;

	memset(&submitInfo, 0, sizeof(submitInfo));
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	/**
	 * Array of command buffers handles
	 */
	submitInfo.pCommandBuffers = &g_commandBuffer;
	if (vkQueueSubmit(computing_queue, 1, &submitInfo, NULL) != VK_SUCCESS)
		return (1);
	{
		printf("Command buffer submission failed\n");
		return (-1);
	}

	return (0);
}