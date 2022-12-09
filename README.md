# Compute shader with Vulkan

Initialization of a Vulkan program to execute a compute shaders.

## Contents
- [Introduction](#Introduction)
- [Requirements](#Requirements)
- [Initialization](#Initialization)

<a name='Introduction'></a>
 
## Introduction

Vulkan is an explicit graphics API, that means it works in a lower level, with low overhead and explicit control, but with the responsibility of the developer to do everything.

Compute shaders are a special type of shader that doesn’t use the fixed graphics pipeline, and just allows to run arbitrary computations on the GPU. The only input CS get, unlike 2D or 3D shaders, aside from API state such as the bound Constant Buffers and resources, is their thread index. CS threads have their own identity and registers.

Generation of an image(1000x1000px) of a simple fractal and compare the processing time(miliseconds) needed by the CPU and the GPU:


#### &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; CPU time: 285 ms.   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;   GPU time: 4 ms.
<p align="left">
 <img height="230px" src="https://github.com/esettes/compute_shader_vulkan/blob/main/img/fractal_cpu.png" />
 <img height="230px" src="https://github.com/esettes/compute_shader_vulkan/blob/main/img/fractal_gpu.png" />
</p>

<a name='Requirements'></a>
 
## Requirements

For Linux platform.

- Vulkan SDK - [Installation guide](https://vulkan.lunarg.com/doc/sdk/1.3.231.2/linux/getting_started.html).
- glslangValidator - Shader compiler to generate SPIR-V `$ apt install glslang-dev glslang-tools`
- GCC compiler `$ apt install gcc`
- Make `$ apt install make`

<a name='Initialization'></a>
 
## Initialization

## 1. Create an instance

The very first thing needed is to create an instance, which is the connection between the application and the Vulkan library. Some details about the application it's specifies to the driver here.

````c
VkInstance  g_instance;

void	create_instance(void)
{
     VkInstanceCreateInfo   instance_info;

     instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
     vkCreateInstance(&instance_info, NULL, &g_instance);
}
```` 

Vulkan's goal is to achieve the best possible performance, so it doesn't handle any kind of exception. If the app crashes, you don't know why. To enable exception or malpractice handling, Vulkan has some type of layers that enable different types of debugging and exception handling. This layers must be declared in the instance. Besides, you also need to create exception handlers throughout the program.

You can check the avaible layers with `vkEnumerateInstanceLayerProperties`.

## 2. Physical device

Enumerate all physical devices from the instance and set with which GPU will the aplication work. `vkGetPhysicalDeviceProperties` used with a `VkPhysicalDeviceProperties` structure allows to see significant information about each device. This info can be seen using any debugger.

```c
VkPhysicalDevice    g_physical_device;

void	get_physical_device()
{
	VkPhysicalDevice    devices[100];
	uint32_t            count = 100;

	vkEnumeratePhysicalDevices(g_instance, &count, devices);
	g_physical_device = devices[0];
}
```

## 3. Queue and Logical device

A __queue__ is the way that an application and the device communicate. A physical device may support different types of queues that originate from different queue families and each family of queues allows only a subset of commands. For example, there could be a queue family that only allows processing of compute commands or one that only allows memory transfer related commands.

Enumerate the supported family queues for the device and then obtain the index for the queue (or queues) needed for the application.

```c
uint32_t    g_compute_queue_index;

void	create_device_and_compute_queue(void)
{
	VkQueueFamilyProperties families[20];
	uint32_t                count = 20;

	vkGetPhysicalDeviceQueueFamilyProperties(g_physical_device, &count, families);
	g_compute_queue_index = 0;
	while ((g_compute_queue_index < count) && ((families[g_compute_queue_index].queueFlags
		& VK_QUEUE_COMPUTE_BIT) == 0))
	{
		g_compute_queue_index++;
	}
```

To interact with the Physical device, a __Logical device__ must be configurated and created. This is where the family queues are specified. If more than one different configuration is needed, several logical devices can be created for the same physical device.

With this, the queue can now be configured, using the logical device and the index of needed queue with a `VkQueue` structure and `vkGetDeviceQueue` function, because in this case it's only one queue create for a family queue. If there are more queues, you have to used `vkGetDeviceQueue2`.

## 3. Command pool - command buffer (?)
.

## 3. Shader module
.

### 3. Shader bindings

Pipeline layout and descriptoor set

### 3. Pipeline
.

### 3. Command buffer
.

### 3. Submit info
.

### 3. Synchronization

Fences are objects used to synchronize the CPU and GPU.




