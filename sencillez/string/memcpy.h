/*
 * MIT License
 *
 * Copyright (c) 2022 Da'Jour J. Christophe. All rights reserved.
 * Copyright (c) 2022 Harpont, Inc. All rights reserved.
 *
 * Implements standard C conventions around a call to the
 * function memcpy.
 */
#ifndef MEMCPY_STRING_SENCILLEZ_GNU99C_H
#define MEMCPY_STRING_SENCILLEZ_GNU99C_H

#include "sencillez/internal/attr.h"
#include "sencillez/internal/flags.h"
#include "sencillez/internal/msg.h"
#include "sencillez/stdlib/die.h"
#include <stddef.h>
#include <string.h>

/*
 * Implements standard C conventions around
 * a call to the function memcpy.
 */
static inline always_inline void _memcpy_(
  void *dst, void const *src, size_t n)
{
#ifdef ENABLED_SIMPLICITY
  if (dst == NULL ||
      src == NULL)   { die(__func__, INVALID_PTR); }
#endif
      memcpy(dst, src, n);
#ifdef ENABLED_STRICT_SIMPLICITY
  if (memcmp(dst, src, n)) { warn(__func__, NOT_CPY); }
#endif
}

#endif /* MEMCPY_STRING_SENCILLEZ_GNU99C_H */
