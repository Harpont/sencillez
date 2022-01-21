/*
 * MIT License
 *
 * Copyright (c) 2022 Da'Jour J. Christophe. All rights reserved.
 * Copyright (c) 2022 Harpont, Inc. All rights reserved.
 *
 * Implement a standardized way of freeing any pointer type.
 */
#ifndef FREE_STDLIB_SENCILLEZ_GNU99C_H
#define FREE_STDLIB_SENCILLEZ_GNU99C_H

#include "sencillez/internal/attr.h"
#include "sencillez/internal/flags.h"
#include "sencillez/internal/stdint.h"
#include <stdlib.h>

/*
 * Implements standard C conventions around
 * a call to the function free.
 */
static inline always_inline void __sencillez_free_pointer__(
  void *__ptr)
{
#ifdef ENABLED_SIMPLICITY
  if (__ptr != NULL) {
#endif
    free(__ptr);
#ifdef ENABLED_SIMPLICITY
    __ptr = NULL; }
#endif
}

/*
 * Implements standard C conventions around
 * freeing an array of pointers.
 */
#ifdef ENABLED_SIMPLICITY
/*
 * Enumerate over the parent pointer's child pointers,
 * with each iteration attempt to free the child.
 */
#define __sencillez_free_children__(__ptr,__itr) \
  for (; __itr; --__itr) { __sencillez_free_pointer__(__ptr[(__itr - 1)]); }

#endif

#endif /* FREE_STDLIB_SENCILLEZ_GNU99C_H */
