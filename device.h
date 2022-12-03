/**
 * @ Author: Roxana Stancu (esettes)
 * @ Created: 22/12/03 02:48
 * @ Modified: 22/12/03 16:00
 * @ Description:
 */

# ifndef DEVICE_H
# define DEVICE_H

#include <vulkan/vulkan.h>

extern VkDevice	g_logicalDevice;
extern VkQueue	g_compQueue;

void	create_device_and_compute_queue(void);

# endif