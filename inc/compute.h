/**
 * @ Author: Roxana Stancu
 * @ Created: 2022/12/02 23:42
 * @ Modified: 2022/12/04 03:10
 */

# ifndef COMPUTE_H
# define COMPUTE_H

#include <vulkan/vulkan.h>
#include <string.h>
#include "device.h"
/**
 * Submits command buffer to queue.
 */
int		compute(void);
/**
 * Alloc command buffer and record dispatch.
 */
void	set_command_buffer(void);

# endif