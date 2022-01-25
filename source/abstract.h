/*
 * MIT License
 *
 * Copyright (c) 2022 Da'Jour J. Christophe. All rights reserved.
 * Copyright (c) 2022 Harpont, Inc. All rights reserved.
 *
 * Define internal static analyzer simplifications.
 */
#ifndef ABSTRACT_SENCILLEZ_H
#define ABSTRACT_SENCILLEZ_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIE(__msg) \
  fprintf(stderr, "%s\n", __msg); \
  exit(EXIT_FAILURE);

#define __SENCILLEZ_OUT_OF_MEMORY__ "malloc(): out of memory"
#define __SENCILLEZ_REG_SYNTAX_ERROR__ "regcomp(): syntax error"

#define MALLOC(__ptr,__n) \
  __ptr = malloc(__n); \
  if (__ptr == NULL) { DIE(__SENCILLEZ_OUT_OF_MEMORY__); } \
  memset(__ptr, 0, __n);

#define FREE(__ptr) \
  if (__ptr != NULL) { free(__ptr); __ptr = NULL; }

#define FREEN(__ptr,__n) \
  for (uint64_t __i_s_i = 0; __i_s_i < __n; __i_s_i++) \
    { FREE(__ptr[__i_s_i]); } \
  FREE(__ptr);

#endif /* ABSTRACT_SENCILLEZ_H */
