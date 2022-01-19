/*
 * MIT License
 *
 * Copyright (c) 2022 Da'Jour J. Christophe. All rights reserved.
 * Copyright (c) 2022 Harpont, Inc. All rights reserved.
 *
 * Internal logging system for writing messages to the stdout and
 * gracefully exiting the programming when an unsafe situation arises.
 */
#ifndef DIE_STDLIB_SIMPLICITY_GNU99C_H
#define DIE_STDLIB_SIMPLICITY_GNU99C_H

#include "simplicity/internal/attr.h"
#include "simplicity/internal/msg.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Write a message to the stdout to notify of an
 * unsafe occurance.
 *
 * NOTE: When compiler optimization is less than two,
 * this function will do nothing.
 */
static inline always_inline void warn(
  char const * __func_name, char const * __msg)
{
  fprintf(stderr, "%s(): %s\n", __func_name, __msg);
}

/*
 * Write a message to the stdout to notify of an
 * unsafe occurance and exit the program.
 *
 * NOTE: When compiler optimization is less than two,
 * this function will not log a message to the stdout.
 */
static inline always_inline void die(
  char const * __func_name, char const * __msg)
{
  fprintf(stderr, "%s(): %s\nAborted\n", __func_name, __msg);
  exit(EXIT_FAILURE);
}

#endif /* DIE_STDLIB_SIMPLICITY_GNU99C_H */
