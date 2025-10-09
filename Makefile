CC      := clang
CFLAGS  := -std=c99 -Wall -Wextra -Werror -O2 -Iinclude
NAME    := minishell

LIB_SRC := lib/put_char.c lib/str_len.c lib/xstrdup.c
SRC_SRC := src/read_line.c src/split_line.c src/builtin_cd.c src/mysh.c
SRCS    := $(LIB_SRC) $(SRC_SRC) main.c
OBJS    := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CFLAGS := -std=c99 -Wall -Wextra -O0 -g -Iinclude
debug: re

asan: CFLAGS := -std=c99 -Wall -Wextra -O1 -g -fsanitize=address -fno-omit-frame-pointer -Iinclude
asan: LDFLAGS := -fsanitize=address
asan: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o minishell_asan

run: all
	./$(NAME)

.PHONY: all clean fclean re debug asan run
