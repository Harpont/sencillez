/*
 * MIT License
 *
 * Copyright (c) 2022 Da'Jour J. Christophe. All rights reserved.
 * Copyright (c) 2022 Harpont, Inc. All rights reserved.
 *
 * Implements standard C conventions around a call to the
 * function strcpy.
 */
#ifndef STRCPY_STRING_SIMPLICITY_GNU99C_H
#define STRCPY_STRING_SIMPLICITY_GNU99C_H

#include "simplicity/internal/attr.h"
#include "simplicity/internal/flags.h"
#include "simplicity/internal/msg.h"
#include "simplicity/stdlib/die.h"
#include <stddef.h>
#include <string.h>

/*
 * Implements standard C conventions around
 * a call to the function strcpy.
 */
static inline always_inline void _strcpy_(
  char *dst, char const *src)
{
#ifdef ENABLED_SIMPLICITY
  if (dst == NULL ||
      src == NULL)   { die(__func__, INVALID_PTR); }
#endif
      strcpy(dst, src);
#ifdef ENABLED_STRICT_SIMPLICITY
  if (strcmp(dst, src)) { warn(__func__, NOT_CPY); }
#endif
}

#endif /* STRCPY_STRING_SIMPLICITY_GNU99C_H */
