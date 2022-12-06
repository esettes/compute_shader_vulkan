/**
 * @ Author: Roxana Stancu (esettes)
 * @ Created: 2022/12/02 23:40
 * @ Modified: 2022/12/06 18:51
 */

#include "compute.h"
#include "instance.h"
#include "device.h"
#include "pipeline.h"
#include "memory.h"

/* Buffers mirrors */
uint32_t	g_in_buffer[1000];
float		g_out_buffer[1000];

int	main(int argc, char **argv)
{
	create_instance();
	get_physical_device();
	create_device_and_compute_queue();
	create_pipeline();
	create_descriptor_set();
	create_buffer(sizeof(g_in_buffer), sizeof(g_out_buffer));
	create_command_pool();
	create_command_buffer();
	compute();
	destroy_pipeline();
	destroy_commandpool_logicaldevice();
	(void)argv;
	(void)argc;
	return (0);
}



// Bind buffer handles with the descriptor set