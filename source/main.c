/*
 * MIT License
 *
 * main.c (c) 2022 Da'Jour J. Christophe. All rights reserved.
 *        (c) 2022 Harpont, Inc. All rights reserved.
 *
 * The start point for the static analyzer program.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int disk_write(void *fdata, char const *fpath, size_t fsize);
int disk_read(void *buffer, char const *fpath);

char **parse(char const *data, size_t *i);
void destroy_lines(char **lines, size_t const n);

/*
 * [x] reading
 * [ ] parsing
 * [ ] formatting
 * [ ] analyzing
 * [ ] inserting
 */

#define MAXFILE  ((1 << (16 - 1)) * sizeof(char  ))

int main(void)
{
  char buffer[MAXFILE];
  int32_t rc = 0;

  memset(buffer, 0, MAXFILE);

  rc = disk_read(buffer, "examples/example.in.c");
  if (rc < 0)
  {
    fprintf(stderr, "%s\n", "main(): could not read file");
    exit(EXIT_FAILURE);
  }

  char **lines = NULL;
  uint64_t i, k;

  lines = parse(buffer, &i);
  if (lines == NULL)
  {
    fprintf(stderr, "%s\n", "main(): could not parse lines");
    exit(EXIT_FAILURE);
  }

  for (k = 0; k < i; k++)
  {
    if (lines[k] != NULL)
    {
      puts(lines[k]);
    }
  }

  destroy_lines(lines, i);

  return 0;
}
