#include "mylib.h"


int str_len(const char *str)
{
  int i = 0;
  for (; str[i] != '\0'; i++);
  return (i);
}
