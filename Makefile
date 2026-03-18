# Compilateur et options
CC      = clang
CFLAGS  = -Wall -Wextra -Werror -O2 -Iinclude 

# Répertoires
SRC_DIR = src
LIB_DIR = lib
BUILD_DIR = build

NAME = minishell

SRC = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(LIB_DIR)/*.c) main.c

OBJ = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking"
	@$(CC) $(CFLAGS) -o $@ $^


$(BUILD_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "Compiling $< -> $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(LIB_DIR)/%.o: $(LIB_DIR)/%.c | $(BUILD_DIR)
	@echo "Compiling"
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo "Compiling $< -> $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/$(SRC_DIR)
	@mkdir -p $(BUILD_DIR)/$(LIB_DIR)

clean:
	@echo "Cleaning files"
	@rm -rf $(BUILD_DIR)


run:
	@echo "Running"
	@cd $(BUILD_DIR)
	@./minishell
