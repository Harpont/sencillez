/*
 * MIT License
 *
 * die.c (c) 2022 Da'Jour J. Christophe. All rights reserved.
 *       (c) 2022 Harpont, Inc. All rights reserved.
 *
 * Provide an example of the how to graceful exit the program.
 */
#include "sencillez/stdlib.h"

int main(void)
{
  die( __func__, INVALID_PTR );
  return 0;
}
