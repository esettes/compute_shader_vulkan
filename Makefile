SRCS = main.c compute.c device.c
HEADERS = compute.h device.h

CC = gcc

CFLAGS = -g -O0
VFLAGS = -lvulkan
TARGET = vulkan_compute

$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) $(VFLAGS) -o $(TARGET)