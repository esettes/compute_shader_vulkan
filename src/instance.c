/**
 * @ Author: Roxana Stancu (esettes)
 * @ Created: 2022/12/03 16:29
 * @ Modified: 2022/12/09 04:19
 * 
 * @ Description: Obtain the physical device.
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

void	get_avaible_layers(void);

VkInstance			g_instance;
VkPhysicalDevice	g_physical_device;

void	get_physical_device()
{
	uint32_t	count = 0;
	uint32_t	gpu_id = 0;

	if (vkEnumeratePhysicalDevices(g_instance, &count, NULL) != VK_SUCCESS)
	{
		printf("[ERROR] Physical devices enumeration failure.\n");
		return ;
	}
	
	VkPhysicalDevice	devices[count];
	
	vkEnumeratePhysicalDevices(g_instance, &count, devices);
	for (uint32_t i = 0; i < count; i++)
	{
		VkPhysicalDeviceProperties	properties;
		VkPhysicalDeviceFeatures	features;

		vkGetPhysicalDeviceProperties(devices[i], &properties);
		vkGetPhysicalDeviceFeatures(devices[i], &features);
		printf("Device found: %s\n", properties.deviceName);
		if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
			gpu_id = i;
	}
	g_physical_device = devices[gpu_id];
}

void	create_instance(void)
{
	const char				*layers[] = { "VK_LAYER_KHRONOS_validation" };
	VkInstanceCreateInfo	instance_info;

	memset(&instance_info, 0, sizeof(instance_info));
	instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instance_info.ppEnabledLayerNames = layers;
	instance_info.enabledLayerCount = 1;
	#if DEBUG == 1
	get_avaible_layers(*layers);
	#endif
	if (vkCreateInstance(&instance_info, NULL, &g_instance) != VK_SUCCESS)
	{
		printf("[ERROR] Instance not created.\n");
		return ;
	}
}

void	get_avaible_layers(void)
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
			return ;
		}
	}
}
