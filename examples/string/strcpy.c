/*
 * MIT License
 *
 * strcpy.c (c) 2022 Da'Jour J. Christophe. All rights reserved.
 *          (c) 2022 Harpont, Inc. All rights reserved.
 *
 * Provide an example of the how to implement a call to memcpy.
 */
#include "simplicity/string.h"
#include <stdio.h>

int main(void)
{
  char a[4];
  char b[4] = "foo";
  _strcpy_ ( a, b );
  puts(a);
  return 0;
}
