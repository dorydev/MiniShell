#include <unistd.h>
#include <string.h>

int str_len(const char *str)
{
  int i = 0;
  for (; str[i] != '\0'; i++);
  return (i);
}

void print_char(const char *s)
{
  write(1, s, str_len(s));
}
