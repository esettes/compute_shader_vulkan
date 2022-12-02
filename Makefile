SRCS = main.c compute.c
HEADERS = compute.h

CC = gcc

CFLAGS = -g -O0
VFLAGS = -lvulkan
TARGET = vulkan_compute

$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) $(VFLAGS) -o $(TARGET)