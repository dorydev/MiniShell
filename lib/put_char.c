#include <unistd.h>
#include "mylib.h"

void put_char(const char *s)
{
  write(1, s, str_len(s));
}
