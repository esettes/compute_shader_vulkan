# --------------------------------------------- #
# @ Author: Roxana Stancu (esettes)             #
# @ Created: 22/12/02 23:38                     #
# @ Modified: 22/12/03 17:58                    #
# --------------------------------------------- #

# --- Colors --- #

GREEN	= \033[0;32m
GREY	= \033[2;37m
RESET	= \033[0;38m
CHECK	= $(GREEN)✓$(RESET)
G_OK	= $(GREEN)[OK]$(RESET)

# --- Target, sources and it's paths --- #

TARGET = comp_shader
SOURCE_DIR = ./src/
SOURCE_NAMES = $(shell ls $(SOURCE_DIR) | grep -E ".+\.c")
SOURCES = $(addprefix $(SOURCE_DIR), $(SOURCE_NAMES))
OBJ_DIR = ./src/obj/
OBJS	= $(addprefix $(OBJ_DIR), $(SOURCE_NAMES:.c=.o))
HEADERS = -I include -I ./inc/

# --- Compiler and flags --- #

CC = gcc

CFLAGS = -g3
VFLAGS = -lvulkan

# --- Rules --- #

all: obj $(TARGET)

obj:
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o:$(SOURCE_DIR)%.c
	@echo "$(GREY)$(notdir $<) $(CHECK)"
	@$(CC) $(CFLAGS) $(VFLAGS) $(HEADERS) -o $@ -c $<

$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) $(HEADERS) -o $(TARGET) $(OBJS) $(VFLAGS)
	@echo "${WHITE}$(TARGET) compilation $(G_OK)"

#$(TARGET): $(SOURCES) $(HEADERS)
#	$(CC) $(CFLAGS) $(SOURCES) $(VFLAGS) -o $(TARGET)

clean: 
	@rm -f $(OBJ_DIR)*.o
	@echo "$(BWHITE)Clean objs $(G_OK)"

fclean: clean
	@rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re 