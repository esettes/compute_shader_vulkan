/**
 * @ Author: Roxana Stancu (esettes)
 * @ Created: 22/12/03 02:48
 * @ Modified: 22/12/03 16:14
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

#include "device.h"

uint32_t	g_compQueueFamilyIndex;
VkDevice	g_logicalDevice = VK_NULL_HANDLE;
VkQueue		g_compQueue = VK_NULL_HANDLE;

void	create_device_and_compute_queue(void)
{
	VkQueueFamilyProperties	families[100];
	uint32_t				f_count = 100;

	/* * * * * *		Get which queue we need			* * * * * */
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &f_count, families);
	printf("Found %u queue families\n", f_count);
	g_compQueueFamilyIndex = 0;
	while ((g_compQueueFamilyIndex < f_count) &&
		((families[g_compQueueFamilyIndex].queueFlags & VK_QUEUE_COMPUTE_BIT) == 0))
	{
		g_compQueueFamilyIndex++;
	}
	/**
	 * If the suitable queue family is not found, print error.
	*/
	if (g_compQueueFamilyIndex == f_count)
	{
		printf("Compute que not found\n");
	}

	/* * * *	Open the device; create the logical device	* * * * * */
	VkDeviceCreateInfo		deviceCreateInfo;
	VkDeviceQueueCreateInfo	queueCreateInfo;
	float					prior = 1.0f;

	memset(&queueCreateInfo, 0, sizeof(queueCreateInfo));
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = g_compQueueFamilyIndex;
	queueCreateInfo.queueCount = 1;
	queueCreateInfo.pQueuePriorities = &prior;
	memset(&deviceCreateInfo, 0, sizeof(deviceCreateInfo));
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
	deviceCreateInfo.queueCreateInfoCount = 1;
	if (vkCreateDevice(physicalDevice, &deviceCreateInfo, NULL, &g_logicalDevice)
		!= VK_SUCCESS)
	{
		printf("Logical device creation failure\n");
		return ;
	}
	/* * * *	Get the compute queue handle	* * * * * */
	vkGetDeviceQueue(g_logicalDevice, g_compQueueFamilyIndex, 0, &g_compQueue);
}