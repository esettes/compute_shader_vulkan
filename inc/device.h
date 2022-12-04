/**
 * @ Author: Roxana Stancu (esettes)
 * @ Created: 22/12/03 02:48
 * @ Modified: 22/12/03 23:01
 * @ Description:
 */

# ifndef DEVICE_H
# define DEVICE_H

#include <vulkan/vulkan.h>

extern VkDevice			g_logical_device;
extern VkQueue			g_compute_queue;
extern VkCommandPool	g_compute_command_pool;

void	create_device_and_compute_queue(void);
void	create_command_pool(void);
void	destroy_commandpool_logicaldevice(void);

# endif