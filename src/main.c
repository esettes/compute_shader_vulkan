/**
 * @ Author: Roxana Stancu (esettes)
 * @ Created: 2022/12/02 23:40
 * @ Modified: 2022/12/07 23:38
 */

#include "compute.h"
#include "instance.h"
#include "device.h"
#include "pipeline.h"
#include "memory.h"
#include <stdio.h>
#include "time.h"

/* Need to map GPUs memory to our memory */
/* Buffers mirrors */
uint32_t	g_in_data[1000];
uint32_t	g_out_data[1000][1000];

void	generate_fractal(void)
{
	uint32_t	height_size = 1000;
	uint32_t	width_size = 1000;
	uint32_t	color = 0;

	for (uint32_t row = 0; row < 1000; row++)
	{
		for (uint32_t col = 0; col < 1000; col++)
		{
			float r = (float)row / 500.0 - 1.0;
			float i = (float)col / 500.0 - 1.0;

			uint32_t count = 0;
			while (((r * r + i * i) < 4.0) && (count < 63))
            {
                float temp = r * r - i * i + 0.17;
                i = 2 * r * i + 0.57;
                r = temp;
				count++;
			}
			/**Color depends on the counter
			 * Shifted to the left by 10 bits and add Alpha so that
			 * the value is a real 32 bit RGB value.
			*/
			g_out_data[row][col] = (count << 10) | 0xff000000;
		}
	}
}

uint32_t	get_time(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
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
	
	
	copy_to_input_buffer(g_in_data, sizeof(g_in_data));
	
	uint32_t	start = get_time();
	generate_fractal();
	start = get_time() - start;
	printf("CPU time: %ums.\n", start);

	FILE *f = fopen("./img/raw/fractal_cpu_1000x100.raw", "wb");
	fwrite(g_out_data, sizeof(g_out_data), 1, f);
	fclose(f);

	start = get_time();
	compute();
	start = get_time() - start;
	printf("GPU time: %ums.\n", start);

	copy_from_output_buffer(g_out_data, sizeof(g_out_data));
	
	f = fopen("./img/raw/fractal_gpu_1000x100.raw", "wb");
	fwrite(g_out_data, sizeof(g_out_data), 1, f);
	fclose(f);

	destroy_pipeline();
	destroy_commandpool_logicaldevice();
	(void)argv;
	(void)argc;
	return (0);
}

/*
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
*/
