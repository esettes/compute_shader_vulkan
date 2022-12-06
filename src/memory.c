/**
 * @ Author: Roxana Stancu (esettes)
 * @ Created: 2022/12/06 14:20
 * @ Modified: 2022/12/06 20:31
 * 
 * @ Description: Alloc memory in the GPU.
 */

#include "memory.h"
#include "device.h"
#include "instance.h"
#include "compute.h"
#include <string.h>
#include <stdio.h>

VkBuffer		g_in_buffer = VK_NULL_HANDLE;
VkBuffer		g_out_buffer = VK_NULL_HANDLE;
VkDeviceMemory	g_in_buffer_mem = VK_NULL_HANDLE;
VkDeviceMemory	g_out_buffer_mem = VK_NULL_HANDLE;

uint32_t	find_mem_index_by_type(uint32_t allowed_types, VkMemoryPropertyFlags flags);
/**
 * Prepare data that will be copied to the GPU
*/
VkBuffer	create_and_alloc_buffer(uint32_t size, VkDeviceMemory *device_mem)
{
	VkBuffer			buffer;
	VkDeviceMemory		buffer_mem;
	VkBufferCreateInfo	buffer_info; /**< buffer handle */

	memset(&buffer_info, 0, sizeof(buffer_info));
	buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	buffer_info.size = size;
	/* if want to use buff in multiple queues, mode would be concurrent */
	buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	buffer_info.usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
	if (vkCreateBuffer(g_logical_device, &buffer_info, NULL, &buffer)
		!= VK_SUCCESS)
	{
		printf("[ERROR] Can't create buffer.\n");
		return (VK_NULL_HANDLE);
	}
	/**
	 * Alloc mem --------------
	 */
	VkMemoryRequirements	mem_requirements;
	/* gives required size of the mem block and allows mem types for buffer */
	vkGetBufferMemoryRequirements(g_logical_device, buffer, &mem_requirements);
	
	VkMemoryAllocateInfo alloc_info;
	
	memset(&alloc_info, 0, sizeof(alloc_info));
	alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	alloc_info.allocationSize = mem_requirements.size;
	alloc_info.memoryTypeIndex = find_mem_index_by_type(
		mem_requirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
		| VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT); /** this flags means visible mem
		and synchronizate, so allows read and write actual data in the GPU */
	if (vkAllocateMemory(g_logical_device, &alloc_info, NULL, &buffer_mem)
		!= VK_SUCCESS)
	{
		printf("[ERROR] Can't allocate memory for buffer.\n");
		vkDestroyBuffer(g_logical_device, buffer, NULL);
		return (VK_NULL_HANDLE);
	}
	if (vkBindBufferMemory(g_logical_device, buffer, buffer_mem, 0)
		!= VK_SUCCESS)
	{
		printf("[ERROR] Can't bind buffer memory.\n");
		vkDestroyBuffer(g_logical_device, buffer, NULL);
		vkFreeMemory(g_logical_device, buffer_mem, NULL);
		return (VK_NULL_HANDLE);
	}
	*device_mem = buffer_mem;
	return (buffer);
}
/**
 * Buffer handle and memory region.
 * Creates GPU memory buffers  and writes it to the descriptor set.
 * 
 * @param in_size: input buffer size
 * @param out_size: output buffer size
 */
void	create_buffers(uint32_t in_size, uint32_t out_size)
{
	g_in_buffer = create_and_alloc_buffer(in_size, &g_in_buffer_mem);
	g_out_buffer = create_and_alloc_buffer(out_size, &g_out_buffer_mem);

	/** Input - output info of descriptor set */
	VkDescriptorBufferInfo descriptor_buff_info[2];
	descriptor_buff_info[0].buffer = g_in_buffer;
	descriptor_buff_info[0].offset = 0;
	descriptor_buff_info[0].range = in_size; /**< want to use as much space as
											allocated. Range = how many bytes 
											should the buff contain. */
	descriptor_buff_info[1].buffer = g_out_buffer;
	descriptor_buff_info[1].offset = 0;
	descriptor_buff_info[1].range = out_size;
	/** Descriptor set*/
	VkWriteDescriptorSet	write_descriptor_set;
	memset(&write_descriptor_set, 0, sizeof(write_descriptor_set));
	write_descriptor_set.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	write_descriptor_set.dstSet = g_descriptor_set;
	write_descriptor_set.dstBinding = 0;
	write_descriptor_set.descriptorCount = 2; /**< num of buffs want to bind with DS,
											input - output */
	write_descriptor_set.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
	write_descriptor_set.pBufferInfo = descriptor_buff_info;
	/* It can bind multiple buffer types to multiple descriptor sets,
	so each operation must be specified */
	vkUpdateDescriptorSets(g_logical_device, 1, &write_descriptor_set, 0, NULL);
}

void	destroy_buffers(void)
{
	vkDestroyBuffer(g_logical_device, g_in_buffer, NULL);
	vkDestroyBuffer(g_logical_device, g_out_buffer, NULL);
	vkFreeMemory(g_logical_device, g_in_buffer_mem, NULL);
	vkFreeMemory(g_logical_device, g_out_buffer_mem, NULL);
}
/**
 * Obtain all memory types and properties, parses all of types that fit
 * into 'allowed_types'.
 * 
 * @param allowed_types: bit mask of allowed indices
 * @param flags: required mem type flags
 * @return index of memory type
 */
uint32_t	find_mem_index_by_type(uint32_t allowed_types, VkMemoryPropertyFlags flags)
{
	VkPhysicalDeviceMemoryProperties	mem_properties; 
	uint32_t							type_mask = 1;

	vkGetPhysicalDeviceMemoryProperties(g_physical_device, &mem_properties);
	/* Shifts the tyoe mask to the left, so in each loop type_mask will have
	i-th bits set. */
	for (uint32_t i = 0; i < mem_properties.memoryTypeCount; i++)
	{
		/* If get in this condition, mem type index i is one of allowed types*/
		if ((allowed_types & type_mask) != 0)
		{
			/* Check if contains required mem flags, if true, ret index of mem type*/
			if (mem_properties.memoryTypes[i].propertyFlags == flags)
				return (i);
		}
	}
	printf("[ERROR] Can't find memory type index.\n");
	return (0);
}
