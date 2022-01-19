/*
 * MIT License
 *
 * warn.c (c) 2022 Da'Jour J. Christophe. All rights reserved.
 *        (c) 2022 Harpont, Inc. All rights reserved.
 *
 * Provide an example of the various warnings that may occur
 * when using this library.
 */
#include "sencillez/stdlib.h"

int main(void)
{
  warn( __func__, INVALID_PTR );
  warn( __func__, INVALID_STR );
  warn( __func__, NOT_CPY );
  warn( __func__, OUT_OF_MEM );

  return 0;
}
