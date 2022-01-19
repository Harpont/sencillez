/*
 * MIT License
 *
 * Copyright (c) 2022 Da'Jour J. Christophe. All rights reserved.
 * Copyright (c) 2022 Harpont, Inc. All rights reserved.
 *
 * Implement a standardized way of freeing any pointer type.
 */
#ifndef FREE_STDLIB_SIMPLICITY_GNU99C_H
#define FREE_STDLIB_SIMPLICITY_GNU99C_H

#include "simplicity/internal/attr.h"
#include "simplicity/internal/flags.h"
#include "simplicity/internal/stdint.h"
#include <stdlib.h>

/*
 * Implements standard C conventions around
 * a call to the function free.
 */
static inline always_inline void _free_ (
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
#define ___free_array___(__ptr,__itr) \
  for (; __itr; --__itr) { _free_ (__ptr[(__itr - 1)]); }
/*
 * Attempt to free all the parent pointer's children
 * and then attempt to free the parent pointer.
 */
#define __free_array__(__ptr,__end) \
  ___free_array___ (__ptr,__end); _free_ (__ptr);
/*
 * Creates inline functions, for freeing pointer
 * arrays, with varying segment lengths.
 */
#define _type__free_array_(__type) \
  static inline always_inline void __type##_free_array_( \
    __type ** __ptr, size_t __end) { __free_array__ (__ptr,__end); }

#include "stdint.h"

_type__free_array_(stdint8_t);
_type__free_array_(stdint16_t);
_type__free_array_(stdint32_t);
_type__free_array_(stdint64_t);

_type__free_array_(int8_t);
_type__free_array_(int16_t);
_type__free_array_(int32_t);
_type__free_array_(int64_t);

_type__free_array_(uint8_t);
_type__free_array_(uint16_t);
_type__free_array_(uint32_t);
_type__free_array_(uint64_t);

#define NOSIGN   0
#define SIGNED   1
#define UNSIGNED 2

static inline always_inline void custom_free(
  void *__ptr, size_t const __len, uint8_t const __signness, size_t __end)
{
  if ( __end == 0 )
  {
    _free_ ( __ptr );
  }
  else
  {
    switch ( __len )
    {
      case sizeof(stdint8_t):
        switch ( __signness )
        {
          case NOSIGN: stdint8_t_free_array_ ( __ptr, __end ); break;
          case SIGNED:    int8_t_free_array_ ( __ptr, __end ); break;
          case UNSIGNED: uint8_t_free_array_ ( __ptr, __end ); break;

          default: break;
        }
      break;

      case sizeof(stdint16_t):
        switch ( __signness )
        {
          case NOSIGN: stdint16_t_free_array_ ( __ptr, __end ); break;
          case SIGNED:    int16_t_free_array_ ( __ptr, __end ); break;
          case UNSIGNED: uint16_t_free_array_ ( __ptr, __end ); break;

          default: break;
        }
      break;

      case sizeof(stdint32_t):
        switch ( __signness )
        {
          case NOSIGN: stdint32_t_free_array_ ( __ptr, __end ); break;
          case SIGNED:    int32_t_free_array_ ( __ptr, __end ); break;
          case UNSIGNED: uint32_t_free_array_ ( __ptr, __end ); break;

          default: break;
        }
      break;

      case sizeof(stdint64_t):
        switch ( __signness )
        {
          case NOSIGN: stdint64_t_free_array_ ( __ptr, __end ); break;
          case SIGNED:    int64_t_free_array_ ( __ptr, __end ); break;
          case UNSIGNED: uint64_t_free_array_ ( __ptr, __end ); break;

          default: break;
        }
      break;

      default: break;
    }
  }
}

#undef ___free_array___
#undef  __free_array__
#undef _type__free_array_
#undef _types_free_array_

#endif

#endif /* FREE_STDLIB_SIMPLICITY_GNU99C_H */
