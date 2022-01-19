/*
 * MIT License
 *
 * malloc.c (c) 2022 Da'Jour J. Christophe. All rights reserved.
 *          (c) 2022 Harpont, Inc. All rights reserved.
 *
 * Provide an example of the how to implement a call to malloc.
 */
#include "sencillez/stdlib.h"
#include <stdlib.h>

int main(void)
{
  char *ptr = NULL;
  ptr = _malloc_ ( 128 );
  if ( ptr != NULL ) { free(ptr); ptr = NULL; }
  return 0;
}
