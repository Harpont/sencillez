/*
 * MIT License
 *
 * parse.c (c) 2022 Da'Jour J. Christophe. All rights reserved.
 *         (c) 2022 Harpont, Inc. All rights reserved.
 *
 * Define a series of functions for parsing C source files.
 */
#include "abstract.h"
#include "io.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAXFILE  ((1 << (16 - 1)) * sizeof(char  ))
#define MAXLINE  ((1 << ( 8 - 1)) * sizeof(char  ))
#define MAXLINES ((1 << ( 5 - 1)) * sizeof(char *))

static char **parse_lines(char *data, size_t *i)
{
  char const chr[2] = "\n";
  char **lines = NULL;
  char *tok = NULL;

  MALLOC(lines, MAXLINES);

  for (tok = strtok(data, chr); tok != NULL; *i += 1, tok = strtok(NULL, chr))
  {
    MALLOC(lines[*i], MAXLINE);
    strcpy(lines[*i], tok);
  }

  return lines;
}

/*
 * [x] reading
 * [ ] parsing
 * [ ] formatting
 * [ ] analyzing
 * [ ] inserting
 */
void parse(char *fpath)
{
  char buffer[MAXFILE];
  int32_t rc = 0;

  memset(buffer, 0, MAXFILE);

  rc = disk_read(buffer, fpath);
  if (rc < 0)
  {
    DIE("main(): could not read file");
  }

  char **lines = NULL;
  uint64_t i, k;

  lines = parse_lines(buffer, &i);
  if (lines == NULL)
  {
    DIE("main(): could not parse lines");
  }

  for (k = 0; k < i; k++)
  {
    if (lines[k] != NULL)
    {
      puts(lines[k]);
    }
  }

  FREEN(lines, i);
}
