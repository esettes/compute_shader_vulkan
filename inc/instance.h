/**
 * @ Author: Roxana Stancu (esettes)
 * @ Created: 2022/12/03 16:36
 * @ Modified: 2022/12/05 01:07
 * 
 * Allocated data buffers must be bound to a descriptor sent and
 * the ds must be bound to the command buffer. This way Vulkan
 * can give the memory to the shader.
 */

# ifndef INSTANCE_H
# define INSTANCE_H

#include <vulkan/vulkan.h>

#ifndef DEBUG
#define DEBUG 1
#endif

extern VkInstance		g_instance;
extern VkPhysicalDevice	g_physical_device;

void	get_physical_device();
void	create_instance(void);

# endif