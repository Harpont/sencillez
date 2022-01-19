/*
 * MIT License
 *
 * memcpy.c (c) 2022 Da'Jour J. Christophe. All rights reserved.
 *          (c) 2022 Harpont, Inc. All rights reserved.
 *
 * Provide an example of the how to implement a call to memcpy.
 */
#include "sencillez/string.h"
#include <stdio.h>

int main(void)
{
  char a[4];
  char b[4] = "foo";
  _memcpy_ ( a, b, 4 );
  puts(a);
  return 0;
}
