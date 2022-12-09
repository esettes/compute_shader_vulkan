# Compute shader with Vulkan

Initialization of a Vulkan program to execute compute shaders based on the Udemy [course](https://www.udemy.com/course/vulkan-gpu-computing/) taught by Miloslav Stofa.

Vulkan is an explicit graphics API, that means it works in a lower level, with low overhead and explicit control, but with the responsibility of the developer to do everything.

Compute shaders are a special type of shader that doesn’t use the fixed graphics pipeline, and just allows to run arbitrary computations on the GPU. The only input CS get, aside from some API states, is their thread index. CS threads have their own identity and registers.

Generation of an image(1000x1000px) of a simple fractal and compare the processing time(miliseconds) needed by the CPU and the GPU:

#### &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; CPU time: 285 ms.   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;   GPU time: 4 ms.
<p align="left">
 <img height="220px" src="https://github.com/esettes/compute_shader_vulkan/blob/main/img/fractal_cpu.png" />
 <img height="220px" src="https://github.com/esettes/compute_shader_vulkan/blob/main/img/fractal_gpu.png" />
</p>

<br>

The steps that I have followed to initialize Vulkan application are summarized [here](https://github.com/esettes/compute_shader_vulkan/wiki/Initialization).
