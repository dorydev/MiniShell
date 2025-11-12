#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "mylib.h"

int sh_loop(void) {

  const char *welcome =
    "\033[1;36m"
    "   /\\_/\\\n"
    "   >^.^<.---.\n"
    "  _'-`-'     )\\\n"
    " (6--\\ |--\\ (`.`-.\n"
    "     --'  --'  ``-'BP\n"
    "-------------------------\n"
    "  Welcome on CatOS =^-^= \n"
    "    The Linux-based mini-os written in C & x86_64 Assembly.\n"
    "\033[0m\n";
    write(1, welcome, strlen(welcome));

    for (;;) {
        if (isatty(STDIN_FILENO)) write(1, "~$ ", 3);

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
