/**
 * @ Author: Roxana Stancu
 * @ Created: 2022/12/02 23:42
 * @ Modified: 2022/12/04 17:23
 */

# ifndef COMPUTE_H
# define COMPUTE_H

#include <vulkan/vulkan.h>
#include <string.h>
#include "device.h"
#include "pipeline.h"

int		compute(void);
void	create_command_buffer(void);

# endif