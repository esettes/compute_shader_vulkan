/**
 * @ Author: Roxana Stancu (esettes)
 * @ Created: 22/12/02 23:41
 * @ Modified: 22/12/03 02:41
 * 
 * @ Description: Alloc command buffer, record dispatch and submit it to queue
 */

#include <vulkan/vulkan.h>
#include <string.h>

VkCommandBuffer g_commandBuffer = VK_NULL_HANDLE;

void	set_command_buffer(void)
{
	VkCommandBufferAllocateInfo allocInfo;

	memset(&allocInfo, 0, sizeof(allocInfo));
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;	/*	cmdPool means where to alloc cmmdBuff from,
												which aren't alloc individually */
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;
	if (vkAllocateCommandBuffers(logicDevice, &allocInfo, &g_commandBuffer)
		!= VK_SUCCESS)
	{
		printf("Command buffer allocation failed\n");
		return ;
	}
	/* Record operations that want to be executed */
	VkCommandBufferBeginInfo beginInfo;
	memset(&beginInfo, 0, sizeof(beginInfo));
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;	/* cmdBuff used once and reset afterwards */

	if (vkBeginCommandBuffer(g_commandBuffer, &beginInfo) != VK_SUCCESS)
	{
		printf("Buffer begining failed\n");
		return ;
	}
	/* 
	 * Now can record various operations to the command buffer 
	 * (x, y, z - multiplied) Run shader in many parallel runs,
	 * can set how many global groups of execs should be run
	 */
	vkCmdDispatch(g_commandBuffer, 1, 1, 1);
	/* 
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
	submitInfo.pCommandBuffers = &g_commandBuffer;	// array of command buffers handles
	if (vkQueueSubmit(computing_queue, 1, &submitInfo, NULL) != VK_SUCCESS)
		return (1);
	{
		printf("Command buffer submission failed\n");
		return (-1);
	}

	return (0);
}