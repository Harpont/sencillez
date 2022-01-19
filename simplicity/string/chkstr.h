/*
 * MIT License
 *
 * Copyright (c) 2022 Da'Jour J. Christophe. All rights reserved.
 * Copyright (c) 2022 Harpont, Inc. All rights reserved.
 *
 * Prior to using a heap string validate such a string.
 */
#ifndef CHKSTR_STRING_SIMPLICITY_GNU99C_H
#define CHKSTR_STRING_SIMPLICITY_GNU99C_H

#include "simplicity/internal/attr.h"
#include "simplicity/internal/flags.h"
#include "simplicity/internal/msg.h"
#include "simplicity/stdlib/die.h"
#include <stddef.h>

/*
 * Validate a string pointer prior to its use.
 */
static inline always_inline void chkstr(
  char *__ptr)
{
#ifdef ENABLED_SIMPLICITY
       if ( __ptr == NULL) { warn(__func__, INVALID_PTR); }
  else if (*__ptr == '\0') { warn(__func__, INVALID_STR); }
#endif
}

#endif /* CHKSTR_STRING_SIMPLICITY_GNU99C_H */
