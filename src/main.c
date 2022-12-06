/**
 * @ Author: Roxana Stancu (esettes)
 * @ Created: 2022/12/02 23:40
 * @ Modified: 2022/12/06 23:02
 */

#include "compute.h"
#include "instance.h"
#include "device.h"
#include "pipeline.h"
#include "memory.h"
#include <stdio.h>

/* Need to map GPUs memory to our memory */
/* Buffers mirrors */
uint32_t	g_in_data[1000];
uint32_t	g_out_data[1000];

void	generate_fractal(void)
{
	uint32_t	height_size = 1000;
	uint32_t	width_size = 1000;

	for (uint32_t row = 0; row < height_size; row++)
	{
		for (uint32_t col = 0; col < width_size; col++)
		{
			float r = (float)row / 500.0 - 1.0;
			float i = (float)col / 500.0 - 1.0;

			uint32_t count = 0;
			while ((r * r * i < 4.0) && (count < 1000))
			{
				float temp = r * r - i * i + 0.17;
				i = 2.0 * r * i + i;
				r = temp + r;
				count++;
			}
			/** Color depends on the counter*/
		}
	}
}

int	main(int argc, char **argv)
{
	create_instance();
	get_physical_device();
	create_device_and_compute_queue();
	create_pipeline();
	create_descriptor_set();
	create_buffers(sizeof(g_in_data), sizeof(g_out_data));
	create_command_pool();
	create_command_buffer();
	
	for (uint32_t i = 0; i < 1000; i++)
	{
		g_in_data[i] = i;
		g_out_data[i] = 0;
	}
	copy_to_input_buffer(g_in_data, sizeof(g_in_data));
	compute();
	copy_from_output_buffer(g_out_data, sizeof(g_out_data));
	for (uint32_t i = 0; i < 1000; i += 50)
	{
		printf("[%u]: %f\n", g_in_data[i], g_out_data[i]);
	}
	destroy_pipeline();
	destroy_commandpool_logicaldevice();
	(void)argv;
	(void)argc;
	return (0);
}
