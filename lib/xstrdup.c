#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *xstrdup(const char *s) {
    if (!s) return NULL;
    size_t n = strlen(s) + 1;
    char *p = (char*)malloc(n);
    if (!p) { perror("malloc"); return NULL; }
    memcpy(p, s, n);
    return p;
}
