# Compute shader with Vulkan

### Initialization of a Vulkan program to execute a compute shader.

## Contents
- [Introduction](#Introduction)
- [Initialization](#Initialization)

<a name='Introduction'></a>
 
## Introduction

Compute shaders are a special type of shader that doesn’t use the fixed graphics pipeline, and just allows to run arbitrary computations on the GPU.

Generation of an image(1000x1000) of a simple fractal and compare the processing time(miliseconds) needed by the CPU and the GPU:


#### &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; CPU time: 285 ms.   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;   GPU time: 4 ms.
<p align="left">
 <img height="230px" src="https://github.com/esettes/compute_shader_vulkan/blob/main/img/fractal_cpu.png" />
 <img height="230px" src="https://github.com/esettes/compute_shader_vulkan/blob/main/img/fractal_gpu.png" />
</p>
<a name='Initialization'></a>
 
## Initialization

### 1. Create an instance

Something that Vulkan have different than another graphics API it's that it add one more step in the process to start to work with GPU. It works with an instance.

Validator layers are included here --

### 2. Obtain physical device

Enumerate all physical devices from the instance. `vkGetPhysicalDeviceProperties` allows to see significant information about each device.

3. 

