/*
 * MIT License
 *
 * Copyright (c) 2022 Da'Jour J. Christophe. All rights reserved.
 * Copyright (c) 2022 Harpont, Inc. All rights reserved.
 *
 * From a single function parse a C file into a format
 * understandable by the static analyzer.
 */
#ifndef PARSE_SENCILLEZ_H
#define PARSE_SENCILLEZ_H

#include <stdint.h>

typedef struct fn_param {
  char *name; /* parameter name */
  char *type; /* parameter type */
} fn_param_t;

typedef struct fn_var {
  uint8_t heap; /* variable heap */
  char *name;   /* variable name */
  char *type;   /* variable type */
} fn_var_t;

typedef struct fn_decl {
  char *name;          /* function name        */
  fn_param_t **params; /* function parameters  */
  char *type;          /* function return-type */
  fn_var_t **vars;     /* function variables   */
} fn_decl_t;

void parse(char *fpath);

#endif /* PARSE_SENCILLEZ_H */
