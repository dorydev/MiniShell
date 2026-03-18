#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#define RL_CHUNK 128

static char *grow_buffer(char *buf, size_t used, size_t *cap) {
    size_t newcap = (*cap >= RL_CHUNK) ? (*cap * 2) : RL_CHUNK;
    if (newcap < used + 1) newcap = used + 1;
    char *newbuf = (char*)malloc(newcap);
    if (!newbuf) return NULL;
    if (buf && used) memcpy(newbuf, buf, used);
    free(buf);
    *cap = newcap;
    return newbuf;
}

char *read_line(void) {
    char  *buffer = NULL;
    size_t cap = 0, pos = 0;

    for (;;) {
        char c;
        ssize_t r = read(STDIN_FILENO, &c, 1);

        if (r == 1) {
            if (c == '\n') {
                if (pos + 1 > cap) {
                    char *t = grow_buffer(buffer, pos, &cap);
                    if (!t) { free(buffer); perror("malloc"); return NULL; }
                    buffer = t;
                }
                buffer[pos] = '\0';
                return buffer;
            }
            if (pos + 1 > cap) {
                char *t = grow_buffer(buffer, pos, &cap);
                if (!t) { free(buffer); perror("malloc"); return NULL; }
                buffer = t;
            }
            buffer[pos++] = c;
        } else if (r == 0) { // EOF
            if (pos == 0) { free(buffer); return NULL; }
            if (pos + 1 > cap) {
                char *t = grow_buffer(buffer, pos, &cap);
                if (!t) { free(buffer); perror("malloc"); return NULL; }
                buffer = t;
            }
            buffer[pos] = '\0';
            return buffer;
        } else { // r == -1
            if (errno == EINTR) continue;
            perror("read");
            free(buffer);
            return NULL;
        }
    }
}
