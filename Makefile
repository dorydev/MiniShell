# Compilateur et options
CC      = gcc
CFLAGS  = -Wall -Wextra -Iinclude

# Répertoires
SRC_DIR = src
LIB_DIR = lib
BUILD_DIR = build

NAME = minishell

SRC = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(LIB_DIR)/*.c) main.c

OBJ = $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(SRC)))

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking"
	@$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "Compiling $< -> $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(LIB_DIR)/%.c | $(BUILD_DIR)
	@echo "Compiling"
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo "Compiling $< -> $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

clean:
	@echo "Cleaning files"
	@rm -rf $(BUILD_DIR)

fclean: clean
	@echo "remove executable"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
