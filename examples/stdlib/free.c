/*
 * MIT License
 *
 * free.c (c) 2022 Da'Jour J. Christophe. All rights reserved.
 *        (c) 2022 Harpont, Inc. All rights reserved.
 *
 * Provide an example of the how to implement a call to free.
 */
#include "sencillez/stdlib.h"
#include <stdlib.h>
#include <string.h>

int main(void)
{
  char *ptr = NULL;

  custom_free ( ptr, 0, NOSIGN, 0 );

  ptr = malloc(128);
  if (ptr == NULL)
  {
    fprintf(stderr, "%s\n", "out of memory");
    exit(EXIT_FAILURE);
  }
  memset(ptr, 0, 128);

  custom_free ( ptr, 0, NOSIGN, 0 );

  return 0;
}
