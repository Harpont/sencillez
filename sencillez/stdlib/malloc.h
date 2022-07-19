/*
 * MIT License
 *
 * Copyright (c) 2022 Da'Jour J. Christophe. All rights reserved.
 * Copyright (c) 2022 Harpont, Inc. All rights reserved.
 *
 * Implement a standardized way of mallocing any pointer type.
 */
#ifndef MALLOC_STDLIB_SIMPLICITY_GNU99C_H
#define MALLOC_STDLIB_SIMPLICITY_GNU99C_H

#include "sencillez/internal/attr.h"
#include "sencillez/internal/flags.h"
#include "die.h"
#include <stdlib.h>
#include <string.h>

/*
 * Implements standard C conventions around
 * a call to the function malloc.
 */
static inline always_inline void * _malloc_(
  size_t const __n)
{
  void * __ptr = NULL;
  __ptr = malloc(__n);
#ifdef ENABLED_SIMPLICITY
  if (__ptr == NULL) { die(__func__, OUT_OF_MEM); }
#ifdef ENABLED_STRICT_SIMPLICITY
  memset(__ptr, 0, __n);
#endif
#endif
  return __ptr;
}

#endif /* MALLOC_STDLIB_SIMPLICITY_GNU99C_H */
