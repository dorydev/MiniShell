#ifndef MYLIB_H
#define MYLIB_H

#include <stddef.h>

void   put_char(const char *s);

int str_len(const char *str);
char  *xstrdup(const char *s);

char  *read_line(void);
char **split_line(char *line);
void   free_argv(char **argv);

int    my_cd(char **argv);
int my_ls(char **argv);

int     sh_loop(void);


#endif
