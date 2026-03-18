#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mylib.h"

char **split_line(char *line) {
    if (!line) return NULL;
    const char *delim = " \t";
    size_t cap = 8, argc = 0;
    char **argv = (char**)malloc(cap * sizeof(*argv));
    if (!argv) { perror("malloc"); return NULL; }

    char *save = NULL;
    char *tok = strtok_r(line, delim, &save);
    while (tok) {
        char *w = xstrdup(tok);
        if (!w) { // cleanup
            for (size_t i=0;i<argc;i++) free(argv[i]);
            free(argv);
            return NULL;
        }
        if (argc + 1 >= cap) {
            size_t newcap = cap * 2;
            char **newv = (char**)malloc(newcap * sizeof(*newv));
            if (!newv) {
                perror("malloc");
                for (size_t i=0;i<argc;i++) free(argv[i]);
                free(argv);
                return NULL;
            }
            for (size_t i=0;i<argc;i++) newv[i] = argv[i];
            free(argv);
            argv = newv; cap = newcap;
        }
        argv[argc++] = w;
        tok = strtok_r(NULL, delim, &save);
    }
    argv[argc] = NULL;
    return argv;
}

void free_argv(char **argv) {
    if (!argv) return;
    for (size_t i=0; argv[i]; i++) free(argv[i]);
    free(argv);
}
