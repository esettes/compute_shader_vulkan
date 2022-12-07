# ------------------------------------------- #
# @ Author: Roxana Stancu (esettes)           #
# @ Created: 2022/12/02 23:38                 #
# ------------------------------------------- #

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

# --- Shader variables --- #
SHADER_SRC = ./src/shader/shader.comp
SHADER_BIN = ./src/shader/bin/shader.spv

# --- Compiler and flags --- #
CC = gcc
CFLAGS = -g3
VFLAGS = -lvulkan

# --- Linking --- #
$(OBJ_DIR)%.o:$(SOURCE_DIR)%.c
	@echo "$(GREY)$(notdir $<) $(CHECK)"
	@$(CC) $(CFLAGS) $(VFLAGS) $(HEADERS) -o $@ -c $<
$(TARGET): $(OBJS) $(SHADER_BIN)
	@$(CC) $(CFLAGS) $(HEADERS) -o $(TARGET) $(OBJS) $(VFLAGS)
	@echo "${WHITE}$(TARGET) compilation $(G_OK)"

# --- Shader compilation --- #
$(SHADER_BIN): $(SHADER_SRC)
	@glslangValidator -V $(SHADER_SRC) -o $(SHADER_BIN)

# --- Rules --- #
all: obj $(TARGET)

obj:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(SOURCE_DIR)/shader/bin/

clean: 
	@rm -f $(OBJ_DIR)*.o
	@rm -f *.raw
	@echo "$(BWHITE)Clean objs $(G_OK)"

fclean: clean
	@rm -f $(SHADER_BIN)
	@rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
