#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "mylib.h"

int sh_loop(void) {
    for (;;) {
        if (isatty(STDIN_FILENO)) write(1, "$> ", 3);

        char *line = read_line();
        if (!line) { if (isatty(STDIN_FILENO)) write(1, "\n", 1); break; }

        char **argv = split_line(line);
        if (argv && argv[0]) {
            if (strcmp(argv[0], "cd") == 0) {
                my_cd(argv);
            } else if (strcmp(argv[0], "ls") == 0) {
                my_ls(argv);
            } else if (strcmp(argv[0], "exit") == 0) {
                free_argv(argv);
                free(line);
                break;
            } else {
                put_char("undefined\n");
            }
        }

        free_argv(argv);
        free(line);
    }
    return 0;
}
