# ********************************* #
#                                   #
# @ Author: Roxana Stancu (esettes) #
# @ Created: 22/12/02 23:38         #
# @ Modified: 22/12/03 17:58        #
# @ Description:                    #
#                                   #
#-----------------------------------#

TARGET = vulkan

SRCS = main.c compute.c device.c instance.c
HEADERS = compute.h device.h instance.h

CC = gcc

CFLAGS = -g -O0 #-Wall -Wextra -Werror
VFLAGS = -lvulkan

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) $(VFLAGS) -o $(TARGET)

clean: 
	rm -f *.o

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re