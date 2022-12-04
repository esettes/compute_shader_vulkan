/**
 * @ Author: Roxana Stancu
 * @ Created: 22/12/02 23:42
 * @ Modified: 22/12/03 16:01
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