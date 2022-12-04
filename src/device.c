/**
 * @ Author: Roxana Stancu (esettes)
 * @ Created: 2022/12/03 02:48
 * @ Modified: 2022/12/04 03:12
 * 
 * @ Description: Open a device and allocate execution queues from it.
 * 
 * A Logical Device is a handle to an opened GPU. When we want
 * to open a GPU, we need to know what queues we're going to use.
 * 
 * Enum all queue families and find that family that supports comp shaders.
 * Prepare a buffer for all families with VkQueueFamilyProperties.
 * For lower waste of memory, set counter param to zero and familyProp to NULL.
 * 
 * vkGetPhysicalDeviceQueueFamilyProperties fills buffer data with queue 
 * families data of a GPU. Indicate in param which of GPU use, if exist more
 * than one, giving an identifier(physical device).
 */

#include <string.h>
#include <stdio.h>
#include "device.h"
#include "instance.h"

uint32_t		g_comp_queue_family_index;
VkDevice		g_logical_device = VK_NULL_HANDLE;
VkQueue			g_compute_queue = VK_NULL_HANDLE;
VkCommandPool	g_compute_command_pool = VK_NULL_HANDLE;

void	create_device_and_compute_queue(void)
{
	VkQueueFamilyProperties	families[100];
	uint32_t				f_count = 100;

	/* * * * * *		Get which queue we need			* * * * * */
	vkGetPhysicalDeviceQueueFamilyProperties(g_physical_device, &f_count,
		families);
	printf("Found %u queue families\n", f_count);
	g_comp_queue_family_index = 0;
	while ((g_comp_queue_family_index < f_count) 
		&& ((families[g_comp_queue_family_index].queueFlags
		& VK_QUEUE_COMPUTE_BIT) == 0))
	{
		g_comp_queue_family_index++;
	}
	/**
	 * If the suitable queue family is not found, print error.
	*/
	if (g_comp_queue_family_index == f_count)
	{
		printf("[ERROR] Compute queue not found\n");
	}
	/* * * *	Open the device; create the logical device	* * * * * */
	VkDeviceCreateInfo		device_create_info;
	VkDeviceQueueCreateInfo	queue_create_info;
	float					prior = 1.0f;

	memset(&queue_create_info, 0, sizeof(queue_create_info));
	queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queue_create_info.queueFamilyIndex = g_comp_queue_family_index;
	queue_create_info.queueCount = 1;
	queue_create_info.pQueuePriorities = &prior;
	memset(&device_create_info, 0, sizeof(device_create_info));
	device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	device_create_info.pQueueCreateInfos = &queue_create_info;
	device_create_info.queueCreateInfoCount = 1;
	if (vkCreateDevice(g_physical_device, &device_create_info, NULL,
		&g_logical_device) != VK_SUCCESS)
	{
		printf("[ERROR] Logical device creation failure\n");
		return ;
	}
	/* * * *	Get the compute queue handle	* * * * * */
	vkGetDeviceQueue(g_logical_device, g_comp_queue_family_index, 0,
		&g_compute_queue);
}

void	create_command_pool(void)
{
	VkCommandPoolCreateInfo		cmd_pool_create_info;

	memset(&cmd_pool_create_info, 0, sizeof(cmd_pool_create_info));
	cmd_pool_create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	cmd_pool_create_info.queueFamilyIndex = g_comp_queue_family_index;
	if (vkCreateCommandPool(g_logical_device, &cmd_pool_create_info, NULL,
		&g_compute_command_pool) != VK_SUCCESS)
	{
		printf("[ERROR] Command pool creation failure\n");
		return ;
	}
}

void	destroy_commandpool_logicaldevice(void)
{
	if (g_compute_command_pool != VK_NULL_HANDLE)
		vkDestroyCommandPool(g_logical_device, g_compute_command_pool, NULL);
	if (g_logical_device != VK_NULL_HANDLE)
		vkDestroyDevice(g_logical_device, NULL);
}
