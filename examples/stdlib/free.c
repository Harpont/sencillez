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

/*
 * If the static analyzer detects that the
 * pointer is of an array-type. It will
 * turn on `__SENCILLEZ_FREE_CHILDREN__` and
 * inject the appropriate code segment along
 * with the number of children it counted.
 */
#ifdef __SENCILLEZ_FREE_CHILDREN__
  __sencillez_free_children__(ptr,);
#endif
  __sencillez_free_pointer__(ptr);
/*
 * No matter what, the static analyzer will attempt
 * to undefine the `__SENCILLEZ_FREE_CHILDREN__`
 * instruction in the event that it was defined.
 */
#ifdef __SENCILLEZ_FREE_CHILDREN__
#undef __SENCILLEZ_FREE_CHILDREN__
#endif

  ptr = malloc(128);
  if (ptr == NULL)
  {
    fprintf(stderr, "%s\n", "out of memory");
    exit(EXIT_FAILURE);
  }
  memset(ptr, 0, 128);

/*
 * If the static analyzer detects that the
 * pointer is of an array-type. It will
 * turn on `__SENCILLEZ_FREE_CHILDREN__` and
 * inject the appropriate code segment along
 * with the number of children it counted.
 */
#ifdef __SENCILLEZ_FREE_CHILDREN__
  __sencillez_free_children__(ptr,);
#endif
  __sencillez_free_pointer__(ptr);
/*
 * No matter what, the static analyzer will attempt
 * to undefine the `__SENCILLEZ_FREE_CHILDREN__`
 * instruction in the event that it was defined.
 */
#ifdef __SENCILLEZ_FREE_CHILDREN__
#undef __SENCILLEZ_FREE_CHILDREN__
#endif

  return 0;
}
