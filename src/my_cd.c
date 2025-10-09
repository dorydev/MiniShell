#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mylib.h"

int my_cd(char **argv) {
    char oldpwd[1024];
    char cwd[1024];

    if (!getcwd(oldpwd, sizeof(oldpwd))) {
        perror("getcwd");
        // on tente quand même le cd; OLDPWD ne sera pas mis à jour si échec
        oldpwd[0] = '\0';
    }

    const char *path = argv[1];
    if (!path) {
        path = getenv("HOME");
        if (!path) { dprintf(2, "cd: HOME not set\n"); return 1; }
    } else if (strcmp(path, "-") == 0) {
        path = getenv("OLDPWD");
        if (!path) { dprintf(2, "cd: OLDPWD not set\n"); return 1; }
        dprintf(1, "%s\n", path); // comme bash
    }

    if (chdir(path) != 0) {
        perror("cd");
        return 1;
    }

    if (getcwd(cwd, sizeof(cwd))) {
        if (oldpwd[0]) setenv("OLDPWD", oldpwd, 1);
        setenv("PWD", cwd, 1);
    } else {
        // pas bloquant, mais on signale
        perror("getcwd");
    }
    return 0;
}
