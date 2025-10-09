#define _POSIX_C_SOURCE 200809L
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "mylib.h"

static int list_one_dir(const char *path) {
    DIR *d = opendir(path);
    if (!d) {
        dprintf(2, "ls: cannot open directory '%s'\n", path);
        return 1;
    }

    struct dirent *ent;
    while ((ent = readdir(d)) != NULL) {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
            continue;
        dprintf(1, "%s\n", ent->d_name);
    }

    closedir(d);
    return 0;
}

int my_ls(char **argv) {
    int rc = 0;

    int nargs = 0;
    for (int i = 1; argv && argv[i]; ++i) nargs++;

    if (nargs == 0) {
        return list_one_dir(".");
    }
    for (int i = 1; argv[i]; ++i) {
        if (nargs > 1) dprintf(1, "%s:\n", argv[i]);
        rc |= list_one_dir(argv[i]);
        if (argv[i+1]) dprintf(1, "\n");
    }
    return rc ? 1 : 0;
}
