#include "mylib.h"
#include <stdio.h>
#include <dirent.h>


int open_dir(int argc, char *argv[])
{
  struct dirent *pDirent;
  DIR *pDir;

  if (argc != 2)
  {
    put_char("Usage: testprog <dirname>\n");
    return 1;
  }

  pDir = opendir (argv[1]);
  if (pDir == NULL) {
    put_char(argv[1]);
    return 1;
  }
  while ((pDirent = readdir(pDir)) != NULL) {
    printf ("[%s]\n", pDirent->d_name);
  }

  closedir (pDir);
  return 0;
}
