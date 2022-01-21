/*
 * MIT License
 *
 * parse.c (c) 2022 Da'Jour J. Christophe. All rights reserved.
 *         (c) 2022 Harpont, Inc. All rights reserved.
 *
 * Define a series of functions for parsing C source files.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE  ((1 << ( 8 - 1)) * sizeof(char  ))
#define MAXLINES ((1 << ( 5 - 1)) * sizeof(char *))

static char **new_lines(size_t n)
{
  char **lines = NULL;
  lines = malloc(n);
  if (lines == NULL)
  {
    fprintf(stderr, "%s\n", "malloc(): out of memory");
    exit(EXIT_FAILURE);
  }
  memset(lines, 0, n);
  return lines;
}

static char *new_line(size_t n)
{
  char *line = NULL;
  line = malloc(n);
  if (line == NULL)
  {
    fprintf(stderr, "%s\n", "malloc(): out of memory");
    exit(EXIT_FAILURE);
  }
  memset(line, 0, n);
  return line;
}

void destroy_lines(char **lines, size_t const n)
{
  uint64_t i;
  for (i = 0; i < n; i++)
    { if (lines[i] != NULL) { free(lines[i]); lines[i] = NULL; }}
  if (lines != NULL) { free(lines); lines = NULL; }
}

char **parse(char const *data, size_t *i)
{
  char **lines = NULL;
  uint64_t j;
  lines = new_lines(MAXLINES);
  for (*i = 0, j = 0; *data; data++)
  {
    if (*i == 0 && j == 0)
    {
      lines[*i] = new_line(MAXLINE);
    }
    if (*data == '\n')
    {
      lines[*i][j] = '\0';
      j = 0; *i += 1;
      lines[*i] = new_line(MAXLINE);
      continue;
    }
    lines[*i][j++] = *data;
  }
  lines[*i][j] = '\0';
  return lines;
}
