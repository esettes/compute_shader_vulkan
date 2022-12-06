/**
 * @ Author: Roxana Stancu (esettes)
 * @ Created: 2022/12/06 14:20
 * @ Modified: 2022/12/06 21:42
 * @ Description:
 */

# ifndef MEMORY_H
# define MEMORY_H

#include <vulkan/vulkan.h>

void	create_buffers(uint32_t in_size, uint32_t out_size);
void	destroy_buffers(void);
void	copy_from_output_buffer(void *data, uint32_t size);
void	copy_to_input_buffer(void *data, uint32_t size);

#endif