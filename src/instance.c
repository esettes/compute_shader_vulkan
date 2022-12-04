/**
 * @ Author: Roxana Stancu (esettes)
 * @ Created: 2022/12/03 16:29
 * @ Modified: 2022/12/04 03:12
 * 
 * @ Description:
 * 
 * Enumerate all GPU's in the system.
 * vkEnumeratePhysicalDevices can be optimized too setting count to zero and
 * decives to NULL.
 * 
 * This way, it will return the number of devices in the system.
 */

#include "instance.h"
#include <string.h>
#include <stdio.h>

int	check_validation_layer_support(void);

VkInstance			g_instance;
VkPhysicalDevice	g_physical_device;

void	get_physical_device()
{
	VkPhysicalDevice			devices[100];
	VkPhysicalDeviceProperties	properties;
	VkPhysicalDeviceFeatures	features;
	uint32_t					count = 100;

	if (vkEnumeratePhysicalDevices(g_instance, &count, devices) != VK_SUCCESS)
	{
		printf("[ERROR] Physical devices enumeration failure.\n");
		return ;
	}
	g_physical_device = devices[0];
	vkGetPhysicalDeviceProperties(devices[0], &properties);
	vkGetPhysicalDeviceProperties(devices[1], &properties);
	vkGetPhysicalDeviceFeatures(devices[0], &features);
	vkGetPhysicalDeviceFeatures(devices[1], &features);
}

void	create_instance(void)
{
	/* const char			*layers[] = { "VK_LAYER_KHRONOS_validation" };*/
	VkInstanceCreateInfo	instance_info;

	memset(&instance_info, 0, sizeof(instance_info));
	instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	#if TEMP_DISABLED
	//#if DEBUG == 1
	if (!check_validation_layer_support())
	{
		printf("Validation layers not supported.\n");
		return ;
	}
	//#endif
	// until I figure out how to do it 
	instance_info.ppEnabledLayerNames = layers;
	instance_info.enabledLayerCount = 1;
	#endif
	if (vkCreateInstance(&instance_info, NULL, &g_instance) != VK_SUCCESS)
	{
		printf("[ERROR] Instance not created.\n");
		return ;
	}
}

int	check_validation_layer_support(void)
{
	uint32_t			layer_count;
	VkLayerProperties	avaible_layers[layer_count];

	vkEnumerateInstanceLayerProperties(&layer_count, NULL);
	vkEnumerateInstanceLayerProperties(&layer_count, avaible_layers);
	for (uint32_t i = 0; i < layer_count; i++)
	{
		printf("Avaible layer: %s\n", avaible_layers[i].layerName);
		if (strcmp("VK_LAYER_KHRONOS_validation", avaible_layers[i].layerName)
			== 0)
		{
			return (0);
		}
	}
	return (1);
}
