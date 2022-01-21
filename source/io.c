/*
 * MIT License
 *
 * io.c (c) 2022 Da'Jour J. Christophe. All rights reserved.
 *      (c) 2022 Harpont, Inc. All rights reserved.
 *
 * This is where all super-set input/output operations are
 * defined.
 */
#include <stdio.h>

int disk_write(void *fdata, char const *fpath, size_t fsize)
{
  FILE *fd = NULL;
  int bytes = 0;
  fd = fopen(fpath, "wb");
  if (fd == NULL) { return -1; }
  bytes = fwrite(fdata, 1, fsize, fd);
  if ((size_t)bytes < fsize) { return -1; }
  if (fd != NULL) { fclose(fd); fd = NULL; }
  return 0;
}

int disk_read(void *fbuff, char const *fpath)
{
  FILE *fd = NULL;
  long fsize;
  int bytes = 0;
  fd = fopen(fpath, "rb");
  if (fd == NULL) { return -1; }
  fseek(fd, 0, SEEK_END);
  fsize = ftell(fd);
  rewind(fd);
  bytes = fread(fbuff, 1, fsize, fd);
  if (bytes != fsize) { return -1; }
  if (fd != NULL) { fclose(fd); fd = NULL; }
  return bytes;
}
