/**
 * @ Author: Roxana Stancu (esettes)
 * @ Created: 22/12/03 16:36
 * @ Modified: 22/12/03 23:34
 * @ Description:
 */

# ifndef INSTANCE_H
# define INSTANCE_H

#include <vulkan/vulkan.h>

#ifndef DEBUG
#define DEBUG 0
#endif

extern VkInstance		g_instance;
extern VkPhysicalDevice	g_physical_device;

void	get_physical_device();
void	create_instance(void);

# endif