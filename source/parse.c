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
#include "parse.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>

#define __SENCILLEZ_OUT_OF_MEMORY__ "malloc(): out of memory"
#define __SENCILLEZ_REG_SYNTAX_ERROR__ "regcomp(): syntax error"

#define MAXFILE  ((1 << (16 - 1)) * sizeof(char  ))
#define MAXLINE  ((1 << ( 8 - 1)) * sizeof(char  ))
#define MAXLINES ((1 << ( 5 - 1)) * sizeof(char *))
#define MAXBUF   ((1 << (11 - 1)) * sizeof(char  ))

#define MAXFUNCS (16 * sizeof(fn_decl_t *))

#define REGEX_MAX_EXPRESSION 128

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

static int32_t regexp(char *value, char *expression, int nmatch)
{
  regex_t regex, *regptr = &regex;
  regmatch_t rm[nmatch];
  char msgbuf[100];
  int32_t reti, spos = -1;

  reti = regcomp(regptr, expression, REG_EXTENDED);
  if (reti)
  {
    DIE((reti == REG_ESPACE) ? strerror(ENOMEM)
                             : __SENCILLEZ_REG_SYNTAX_ERROR__);
  }

  reti = regexec(regptr, value, nmatch, rm, 0);
  if (reti == 0)
  {
    // printf("start: %lu, end: %lu\n", rm[0].rm_so, rm[0].rm_eo);
    spos = rm[0].rm_eo;
  }
  else if (reti == REG_NOMATCH)
  {
  }
  else
  {
    regerror(reti, regptr, msgbuf, sizeof(msgbuf));
    fprintf(stderr, "regexec(): %s\n", msgbuf);
    exit(EXIT_FAILURE);
  }

  regfree(regptr);
  return spos;
}

static int32_t regexpn(char *buffer, char **exprs, size_t n)
{
#define REGEX_EXPECTED_RESULTS 1
  int32_t status = 0, pos = 0, tmp = pos;
  uint64_t i;

  for (i = 0; i < n; pos += tmp, i++)
  {
    tmp = regexp((buffer+pos), exprs[i], REGEX_EXPECTED_RESULTS);
    if (tmp < 0) { status = -1; break; }
  }

#undef REGEX_EXPECTED_RESULTS
  return status;
}

static ssize_t is_func_pred(char **lines,
  size_t const pos, size_t const n)
{
  int64_t const end = (n + pos);
  int64_t i, j;
  uint8_t opened = 0,
          closed = 0;

  for (i = pos; i < end; i++)
  {
    for (j = 0; lines[i][j] != '\0'; j++)
    {
           if ('{' == lines[i][j] &&  opened &&  closed) { goto DONE;  }
      else if ('(' == lines[i][j] && !opened           ) { opened = 1; }
      else if (')' == lines[i][j] &&  opened && !closed) { closed = 1; }
    }
  }

DONE:
  return ((opened && closed) ? (i+1) : (-1));
}

static size_t is_func_join(char **lines, char *buf, size_t begin, size_t n)
{
  size_t end;
  uint64_t i;
  end = is_func_pred(lines, begin, n);
  for (i = begin; i < end; i++)
  {
    if (lines[i] == NULL) { continue; }
    strcat(buf, lines[i]);
  }
  return end;
}

static inline uint8_t is_letter(char const ch)
{
  return ((ch >= 65 && ch <=  90) ||
          (ch >= 97 && ch <= 122));
}
static inline uint8_t is_number(char const ch)
{
  return (ch >= 48 && ch <= 57);
}
static inline uint8_t is_whitespace(char const ch)
{
  return (ch == 9 || ch == 10 || ch == 32);
}

static char *parse_name(char *tmp, char *src)
{
  for (; *src != '\0'; tmp++, src++)
  {
    if ('(' == *src) { break; }
    *tmp = *src;
  }

  return src;
}

static char *parse_type(char *tmp, char *src)
{
  uint8_t threshold = 0;

  for (; *src != '\0'; tmp++, src++)
  {
    if (!threshold && ('*' == *src || is_whitespace(*src))) { threshold = 1; }
    else if (threshold && is_letter(*src)) { *tmp = '\0'; break; }
    *tmp = *src;
  }

  return src;
}

static fn_decl_t *new_fn_decl(void)
{
  fn_decl_t *fn = NULL;

  MALLOC(fn,             sizeof(fn_decl_t));
  MALLOC(fn->type, (32 * sizeof(char)));
  MALLOC(fn->name, (64 * sizeof(char)));

  return fn;
}

static fn_decl_t *format(char *src)
{
  fn_decl_t *fn = NULL;

  fn = new_fn_decl();

  src = parse_type(fn->type, src);
  src = parse_name(fn->name, src);

  return fn;
}

static void destroy_fn_decl(fn_decl_t *fn)
{
  FREE(fn->type);
  FREE(fn->name);
  FREE(fn);
}

static void print_func(fn_decl_t const *fn)
{
  char const fmt[] = "name: %s\ntype: %s\n\n";
  printf(fmt, fn->name, fn->type);
}

static inline __attribute__ ((always_inline)) char *skipper(char *buf)
{
  for (; *buf != '\0'; buf++)
    { if ('_' == *buf || is_letter(*buf)) { break; }}
  return buf;
}

static void destroy_fn_decls(fn_decl_t **funcs, size_t const n)
{
  for (int64_t j = n; j > -1; --j)
    { destroy_fn_decl(funcs[j]); }
  FREE(funcs);
}

static char *is_func(char **lines, char **exprs,
  char *buffer, ssize_t *pos, size_t n)
{
#define REGEX_EXPRESSIONS_COUNT 4
  int32_t rc;
  *pos = is_func_join(lines, buffer, *pos, n);
  if (*pos < 0) { FREE(buffer); return NULL; }
  buffer = skipper(buffer);
  rc = regexpn(buffer, exprs, REGEX_EXPRESSIONS_COUNT);
  if (rc < 0) { FREE(buffer); return NULL; }
#undef REGEX_EXPRESSIONS_COUNT
  return buffer;
}

static fn_decl_t **parse_funcs(char **lines, size_t *i, ssize_t n)
{
  char *exprs[REGEX_MAX_EXPRESSION] = {
    "^[[:alnum:]_*]+", "^[[:blank:]]+",
    "^[[:alnum:]*]+", "^\\([[:alnum:][:blank:],_*\n]+\\)", };

  fn_decl_t **funcs = NULL;
  char *buffer = NULL, *tmp = NULL;
  ssize_t pos = 0;

  MALLOC(buffer, MAXBUF);
  MALLOC(funcs, MAXFUNCS);

  tmp = buffer;

  for (*i = 0; pos < n; *i += 1)
  {
    memset(buffer, 0, MAXBUF);
    tmp = is_func(lines, exprs, tmp, &pos, n);
    if (tmp == NULL) { destroy_fn_decls(funcs, (*i-1)); return NULL; }
    funcs[*i] = format(tmp);
  }

  FREE(buffer);
  return funcs;
}

static void print_funcs(fn_decl_t **funcs, size_t const n)
{
  uint64_t i;
  for (i = 0; i < n; i++)
    { print_func(funcs[i]); }
}

/*
 * [x] reading
 * [ ] parsing
 *    [x] sort function scopes
 *    [ ] track local variables created in a function scope
 *    [ ] determine if scoped variable's life extends beyonds
 *        local function scope, if so determine when the
 *        variable falls off a single function scope. Insert
 *        the library heap allocation code and heap free code.
 * [x] formatting
 *    [x] create a schema for tracking scoped variables
 * [ ] analyzing
 *    [ ] write an algorithmn that parses the scoped variable
 *        schemas to determine if the variables are stack
 *        variables or heap variables
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
  uint64_t i;

  lines = parse_lines(buffer, &i);
  if (lines == NULL)
  {
    DIE("main(): could not parse lines");
  }

  fn_decl_t **funcs = NULL;
  size_t n = 0;

  funcs = parse_funcs(lines, &n, i);
  if (funcs == NULL) { DIE("could not parse functions from file"); }

  FREEN(lines, i);
  print_funcs(funcs, n);
  destroy_fn_decls(funcs, --n);
}
