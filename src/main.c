/**
 * @ Author: Roxana Stancu (esettes)
 * @ Created: 2022/12/02 23:40
 * @ Modified: 2022/12/04 14:26
 */

#include "compute.h"
#include "instance.h"
#include "device.h"
#include "pipeline.h"

int	main(int argc, char **argv)
{
	create_instance();
	get_physical_device();
	create_device_and_compute_queue();
	create_pipeline();
	create_command_pool();
	create_command_buffer();
	compute();
	destroy_pipeline();
	destroy_commandpool_logicaldevice();
	(void)argv;
	(void)argc;
	return (0);
}
